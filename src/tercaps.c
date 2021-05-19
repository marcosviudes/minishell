/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tercaps.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 15:18:24 by cnavarro          #+#    #+#             */
/*   Updated: 2021/05/19 12:10:13 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_tercaps(t_shell *shell)
{
	char	*tname;
	char	tbuf[1024];
	
	tname = getenv("TERM");
	tgetent(tbuf, tname);
	shell->tcps = malloc(sizeof(t_tercaps) * TERCAPS_MAX);
	shell->tcps[0].name = tgetstr("up", NULL);
	shell->tcps[0].func = *tcps_up;
	shell->tcps[1].name = tgetstr("do", NULL);
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
	//while (i < TERCAPS_MAX)
	while(i < 2)
	{
		if (ft_strncmp(shell->tcps[i].name, str, ft_strlen(shell->tcps[i].name)) == 0)
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
	write(1, "up\n", 3);
	return (1);
}

int	tcps_down(t_shell *shell)
{
	write(1, "down\n", 5);
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