/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamkhan <ylamkhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 01:02:25 by ylamkhan          #+#    #+#             */
/*   Updated: 2023/05/11 01:02:26 by ylamkhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "philosophers.h"

t_list  *ft_lstnew(int content, int left, int right, char **av)
{
    t_list  *new;
    new = malloc(sizeof(t_list));
    if (new == NULL)
        return (NULL);
    new->philos = content;
	new->left = left;
	new -> fork = 0;
	new->last_eat = 0;
	new ->eated = 0;
	new->right = right;
	new->philosophers = ft_atoi(av[1]);
    new->t_die = ft_atoi(av[2]);
    new->t_eat = ft_atoi(av[3]);
    new->t_sleep = ft_atoi(av[4]);
	if (av[5])
		new->nb_eat = ft_atoi(av[5]);
	else
	 	new->nb_eat = 0;
    new -> next = NULL;
    return (new);
}

t_data  *ft_lstnews(int content)
{
    t_data  *new;
    new = malloc(sizeof(t_data));
    if (new == NULL)
        return (NULL);
    new -> philosophers = content;
    new -> next = NULL;
    return (new);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (lst)
	{
		while (lst->next != NULL)
			lst = lst -> next;
	}
	return (lst);
}

t_data	*ft_data(t_list *lst)
{
	if (lst)
	{
		while (lst->next != NULL)
			lst = lst -> next;
	}
	return (lst->next_data);
}

void	ft_lst_add_backs(t_list **lst, t_data *new)
{
	t_list *tmp;

	if (*lst)
	{
		tmp = ft_lstlast(*lst);
		tmp -> next_data = new;
	}
}

void	ft_lst_add_back(t_list **lst, t_list *new)
{
	t_list *tmp;

	if (*lst)
	{
		tmp = ft_lstlast(*lst);
		tmp -> next = new;
	}
	else
		*lst = new;
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	ret;

	i = 0;
	sign = 1;
	ret = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		ret = ret * 10 + (str[i] - 48);
		i++;
	}
	return (ret * sign);
}
