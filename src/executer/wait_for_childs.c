/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_childs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 01:24:24 by mviudes           #+#    #+#             */
/*   Updated: 2021/10/27 01:24:24 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	wait_for_childs(t_shell *shell, int num_commands)
{
	int	status;
	int	i;

	i = 0;
	while (i < num_commands + 1)
	{
		wait(&status);
		if (WIFEXITED(status))
			shell->return_value = WEXITSTATUS(status);
		i++;
	}
}
