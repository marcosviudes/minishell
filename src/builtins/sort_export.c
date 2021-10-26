/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 01:23:40 by mviudes           #+#    #+#             */
/*   Updated: 2021/10/27 01:23:41 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**ft_matrixdup(char **arr)
{
	int		i;
	char	**ret;

	i = 0;
	ret = malloc(sizeof(char *) * (count_lines(arr) + 1));
	while (arr[i])
	{
		ret[i] = ft_strdup(arr[i]);
		i++;
		ret[i] = NULL;
	}
	return (ret);
}

char	**order_envs(char **envs)
{
	char	**ordered;
	char	*tmp;
	int		i;
	int		j;

	ordered = ft_matrixdup(envs);
	i = 0;
	while (i < count_lines(envs))
	{
		j = 1;
		while (ordered[j])
		{
			if (ft_strncmp(ordered[j - 1], ordered[j],
					(ft_strlen(ordered[j - 1]) + 1)) > 0)
			{
				tmp = ordered[j - 1];
				ordered[j - 1] = ordered[j];
				ordered[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (ordered);
}
