/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dllst_first.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 21:31:37 by mviudes           #+#    #+#             */
/*   Updated: 2021/05/12 22:20:06 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dllst.h>

t_dllist	*dllst_first(t_dllist *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->prev != NULL)
		lst = lst->prev;
	return (lst);
}
