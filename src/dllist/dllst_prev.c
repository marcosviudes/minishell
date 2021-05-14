/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dllst_prev.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 21:31:37 by mviudes           #+#    #+#             */
/*   Updated: 2021/05/12 22:17:40 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dllst.h>

t_dllist	*dllst_prev(t_dllist *lst)
{
	if (lst == NULL)
		return (NULL);
	lst = lst->prev;
	return (lst);
}
