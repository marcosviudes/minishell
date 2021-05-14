/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dllstadd_front.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 21:18:42 by mviudes           #+#    #+#             */
/*   Updated: 2021/05/12 22:19:40 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dllst.h>

void	dllstadd_front(t_dllist **head, t_dllist *new)
{
	new->next = (*head);
	new->prev = NULL;
	if ((*head) != NULL)
		(*head)->prev = new;
	(*head) = new;
}
