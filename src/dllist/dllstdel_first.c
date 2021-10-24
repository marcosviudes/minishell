/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dllstdel_first.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnavarro <cnavarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 20:52:32 by mviudes           #+#    #+#             */
/*   Updated: 2021/10/24 12:34:52 by cnavarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dllst.h>

void	dllstddel_first(t_dllist **first)
{
	t_dllist	*temp;

	if (!first || !*first)
		return ;
	while ((*first)->prev != NULL)
		*first = (*first)->prev;
	temp = *first;
	(*first) = (*first)->next;
	(*first)->prev = NULL;
	free(temp->buff);
	free(temp);
}
