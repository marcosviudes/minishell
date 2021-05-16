/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dllst.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 21:04:48 by mviudes           #+#    #+#             */
/*   Updated: 2021/05/16 21:13:19 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DLLST_H
# define DLLST_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_dllist
{
	char			*buff;
	struct s_dllist	*prev;
	struct s_dllist	*next;
}					t_dllist;

void		ft_dllstclear(t_dllist **lst, void(*del)(void*));
t_dllist	*dllst_first(t_dllist *lst);
t_dllist	*dllst_last(t_dllist *lst);
t_dllist	*dllist_new(char *content);
t_dllist	*dllst_next(t_dllist *lst);
t_dllist	*dllst_prev(t_dllist *lst);
void		dllstadd_back(t_dllist **lst, t_dllist *new);
void		dllstadd_front(t_dllist **alst, t_dllist *new);
void		dllstddel_first(t_dllist **first);
void		dllstddel_last(t_dllist **last);
#endif