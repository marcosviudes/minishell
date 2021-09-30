/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinchar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnavarro <cnavarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 16:36:34 by cnavarro          #+#    #+#             */
/*   Updated: 2021/06/10 17:24:46 by cnavarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinchar(char *s, char c)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc(ft_strlen(s) + 2);
	while (s[i] != '\0')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = c;
	dest[i + 1] = '\0';
	free(s);
	return (dest);
}
