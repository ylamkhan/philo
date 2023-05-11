/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamkhan <ylamkhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 01:02:43 by ylamkhan          #+#    #+#             */
/*   Updated: 2023/05/11 01:02:44 by ylamkhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef PHILOSOPHERS_H

#define PHILOSOPHERS_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_data
{
    pthread_mutex_t *chopkits;
    pthread_mutex_t write;
    int philosophers;
    struct timeval beggin;
    struct s_data *next;
}   t_data;

typedef struct s_list
{
    pthread_t t_id;
    struct timeval current;
    size_t t_eat;
    size_t t_die;
    size_t t_sleep;
    int left;
    int right;
    int philos;
    int philosophers;
    int fork;
    int nb_eat;
    int eated;
    size_t last_eat;
    struct s_list *next;
    t_data *next_data;
}   t_list;

int	ft_atoi(const char *str);
t_list  *ft_lstnew(int content, int left, int right, char **av);
t_data  *ft_lstnews(int content);
t_list	*ft_lstlast(t_list *lst);
void	ft_lst_add_back(t_list **lst, t_list *new);
void	ft_lst_add_backs(t_list **lst, t_data *new);
t_data	*ft_data(t_list *lst);

#endif
