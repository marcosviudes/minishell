/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tercaps.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnavarro <cnavarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 15:18:24 by cnavarro          #+#    #+#             */
/*   Updated: 2021/05/18 17:28:47 by cnavarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_tercaps *init_tercaps(t_shell *shell)
{
	shell->tcps = malloc(sizeof(shell->tcps) * TERCAPS_MAX);
	shell->tcps[0].name = "up";
	shell->tcps[0].func = (*tcps_up);
	shell->tcps[1].name = "down";
	shell->tcps[1].func = (*tcps_down);
	shell->tcps[2].name = "right";
	shell->tcps[2].func = (*tcps_right);
	shell->tcps[3].name = "left";
	shell->tcps[3].func = (*tcps_left);
}

void tercaps(char *str, t_shell *shell)
{
	int i;

	i = 0;
	while (i < TERCAPS_MAX)
	{
		if (ft_strncmp(shell->tcps[i].name, str, ft_strlen(str)) == 0)
			if (shell->tcps[i].func(shell))
				break ;
		i++;
	}
	if (i >= TERCAPS_MAX)
	{
		write(1, &str, ft_strlen(str));
		write(1, " is not a tercap\n", 16);
	}
}

int	tcps_up(t_shell *shell)
{
	write(1, "up", 2);
	return (0);
}

int	tcps_down(t_shell *shell)
{
	write(1, "dw", 2);
	return (0);
}

int	tcps_right(t_shell *shell)
{
	write(1, "rh", 2);
	return (1);
}
int	tcps_left(t_shell *shell)
{
	write(1, "lf", 2);
	return (0);
}