/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 16:22:52 by mviudes           #+#    #+#             */
/*   Updated: 2021/05/12 22:10:12 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dest;
	char		*source;
	size_t		i;

	i = 0;
	dest = (char *)dst;
	source = (char *)src;
	if (dest == NULL && source == NULL)
		return (dst);
	if (src > dst)
	{
		while (i < len)
		{
			dest[i] = source[i];
			i++;
		}
	}
	else if (src < dst)
	{
		i = len;
		while (i-- > 0)
			dest[i] = source[i];
	}
	return (dst);
}
