/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dllst_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 21:08:58 by mviudes           #+#    #+#             */
/*   Updated: 2021/05/12 22:17:40 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dllst.h>

t_dllist	*dllist_new(char *content)
{
	t_dllist	*new;

	new = malloc(sizeof(t_dllist));
	if (!new)
		return (NULL);
	new->buff = content;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}
