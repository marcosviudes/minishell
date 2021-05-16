/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dllstdel_last.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 21:06:12 by mviudes           #+#    #+#             */
/*   Updated: 2021/05/16 21:41:34 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dllst.h>


//Didn`t work jet;

void	dllstddel_last(t_dllist **lst)
{
	t_dllist *prev = NULL;
	t_dllist *cur = NULL;

	if(lst == NULL || *lst == NULL) 
	return;

	if((*lst)->next == NULL) {
	free(*lst);
	*lst = NULL;
	}
	prev = *lst;
	cur = prev->next;
	while(cur->next) {
	prev = prev->next;
	cur = cur->next;
	}
	prev->next = NULL;
	free(cur);
}