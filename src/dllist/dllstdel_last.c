/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dllstdel_last.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnavarro <cnavarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 21:06:12 by mviudes           #+#    #+#             */
/*   Updated: 2021/10/24 12:38:30 by cnavarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dllst.h>

//Didn`t work jet;
void	dllstddel_last(t_dllist **lst)
{
	t_dllist	*prev;
	t_dllist	*cur;

	prev = NULL;
	cur = NULL;
	if (lst == NULL || *lst == NULL)
		return ;
	if ((*lst)->next == NULL)
	{
		free(*lst);
		*lst = NULL;
	}
	prev = *lst;
	cur = prev->next;
	while (cur->next)
	{
		prev = prev->next;
		cur = cur->next;
	}
	prev->next = NULL;
	free(cur);
}
