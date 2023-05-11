/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamkhan <ylamkhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 01:02:54 by ylamkhan          #+#    #+#             */
/*   Updated: 2023/05/11 01:02:55 by ylamkhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "philosophers.h"

void    ft_usleep(int n)
{
    size_t i;
    size_t time;
    struct timeval beggin;
    struct timeval current;

    gettimeofday(&beggin, NULL);
    i = (beggin.tv_sec * 1000000  + beggin.tv_usec);
    i /= 1000;
    while (1)
    {
        usleep(1);
        gettimeofday(&current, NULL);
        time = (current.tv_sec * 1000000 + current.tv_usec);
        time /= 1000;
        if ((time - i) == n)
            break;
    }
}

size_t  get_time(t_list *lst)
{
    size_t res;
    size_t current;
    t_data *data = ft_data(lst);

    gettimeofday(&lst->current, NULL);
    res = (data->beggin.tv_sec * 1000000  + data->beggin.tv_usec);
    current = (lst->current.tv_sec * 1000000 + lst->current.tv_usec);
    res /= 1000;
    current /= 1000;
    return (current - res);
}

int t_die(t_list *lst)
{
    if ((get_time(lst) - lst->last_eat) >= lst->t_die)
    {
        lst->last_eat = 0;
        return(1);
    }
    return (0);
}

int ft_check_params(char **av)
{
    if (ft_atoi(av[1]) <= 0)
        return(1);
    else if (ft_atoi(av[2]) <= 0)
        return(1);
    else if (ft_atoi(av[3]) <= 0)
        return(1);
    else if (ft_atoi(av[4]) <= 0)
        return(1);
    return (0);
}

void    think(t_list *lst)
{
    printf("%ld %d is thinking\n", get_time(lst),lst->philos);
}

void    ft_sleep(t_list *lst)
{
    printf("%ld %d is sleeping\n", get_time(lst),lst->philos);
    ft_usleep(lst->t_sleep);
    think(lst);
}

void    forks(t_list *lst)
{
    t_data *data;
    int     n;

    data = ft_data(lst);
    n = lst->philos;
    pthread_mutex_lock(&data->chopkits[lst->right]);
    printf("%ld %d has taken a fork\n", get_time(lst) ,lst->philos);
    pthread_mutex_lock(&data->chopkits[lst->left]);
    printf("%ld %d has taken a fork\n", get_time(lst) ,lst->philos);
    printf("%ld %d is eating\n", get_time(lst) ,lst->philos);
    lst->last_eat = get_time(lst);
    ft_usleep(lst->t_eat);
    pthread_mutex_unlock(&data->chopkits[lst->left]);
    pthread_mutex_unlock(&data->chopkits[lst->right]);
    ft_sleep(lst);
}

void    *routine(void *arg)
{
    t_list *lst = (void *) arg;
    int i = 1;

    if ((lst->philos % 2) == 0)
        ft_usleep((lst->t_sleep / 2));
    if (lst->nb_eat)
    {
        while (lst->eated < lst->nb_eat)
        {
            forks(lst);
            if (lst->eated == lst->nb_eat)
                break;
            lst->eated++;
        }
    }
    else
    {
        while (1)
            forks(lst);
    }
    return (0);
}

int check_if_died(t_list **lst)
{
    t_list *tmp;
    t_data *data;

    tmp = (*lst);
    data = ft_data(*lst);
    while (1)
    {
        if (tmp->nb_eat)
        {
            if (tmp->eated == tmp->nb_eat)
                return (0);
        }
        if (t_die(tmp) != 0)
        {
            printf("%ld %d is died\n", get_time(tmp) ,tmp->philos);
            return (1);
        }
        if (tmp -> next == NULL)
            tmp = (*lst);
        else
            tmp = tmp -> next;
    }
    return (0);
}

int    join(t_list *lst)
{
    t_list *tmp;

    tmp = lst;
    while (tmp)
    {
        if (pthread_join(tmp->t_id, NULL) != 0)
        {
            write(1, "Error\n", 6);
            return (1);
        }
        tmp = tmp->next;
    }
    return (0);
}

int creat(t_list *lst)
{
    t_list *tmp;

    tmp = lst;
    while (tmp)
    {
        if (pthread_create(&tmp->t_id, NULL, routine, tmp) != 0)
        {
            write(1, "Error\n", 6);
            return (1);
        }
        tmp = tmp->next;
    }
    return (0);
}

int chopkits(t_list *lst)
{
    int i;
    t_data *data;
    t_list *tmp;
    pthread_mutex_t chopkits[lst->philosophers];
    pthread_t *t_id;

    i = 0;
    tmp = lst;
    data = ft_data(lst);
    data->chopkits = malloc(sizeof(pthread_mutex_t) * data->philosophers);
    gettimeofday(&data->beggin, NULL);
    while (i < tmp->philosophers)
    {
        if(pthread_mutex_init(&data->chopkits[i], NULL) != 0)
        {
            write(1, "Error\n", 6);
            return (1);
        }
        i++;
    }
    return (0);
}

int    philosophers(t_list *lst)
{
    if (chopkits(lst) != 0)
        return (1);
    if (creat(lst) != 0)
        return (1);
    if (check_if_died(&lst) != 0)
        return(1);
    //if (join(lst) != 0)
    //    return (1);
    return (0);
}

t_list    *data(char **av)
{
    t_list *lst;
    t_data *data;
    int i;
    int j;
    int k;

    lst = NULL;
    data = NULL;
    i = 1;
    j = 0;
    k = 1;
    while (i <= ft_atoi(av[1]))
    {
        if (i == ft_atoi(av[1]))
            ft_lst_add_back(&lst, ft_lstnew(i, 0, j, av));
        else
            ft_lst_add_back(&lst, ft_lstnew(i, k, j, av));
        i++;
        k++;
        j++;
    }
    data = ft_lstnews(ft_atoi(av[1]));
    ft_lst_add_backs(&lst, data);
    return (lst);
}

int main(int ac, char **av)
{
    t_list *lst;

    if (ac > 4 && ac < 7)
    {
        if (ft_check_params(av) != 0)
        {
            write(1, "Error\n", 6);
            return (1);
        }
        lst = data(av);
        if (philosophers(lst) != 0)
            return (1);
    }
    return (0);
}
