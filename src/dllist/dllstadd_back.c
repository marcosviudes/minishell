/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dllstadd_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 21:09:34 by mviudes           #+#    #+#             */
/*   Updated: 2021/05/12 22:19:04 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dllst.h>

void	dllstadd_back(t_dllist **lst, t_dllist *new)
{
	t_dllist	*last;

	new->next = NULL;
	if (*lst != NULL)
	{
		new->prev = NULL;
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
	new->prev = last;
}
