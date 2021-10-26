/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 01:24:20 by mviudes           #+#    #+#             */
/*   Updated: 2021/10/27 01:24:20 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	redirfds(t_cmd_table *temp_cmd_table,
		int fd[2], int last_fd[2], t_shell *shell)
{
	if (temp_cmd_table->num_command != IS_NODE_FIRST)
	{
		close(last_fd[WRITE_END]);
		dup2(last_fd[READ_END], STDIN_FILENO);
		close(last_fd[READ_END]);
	}
	if (temp_cmd_table->num_command == IS_NODE_MIDLE
		|| temp_cmd_table->num_command == IS_NODE_FIRST)
		dup2(fd[WRITE_END], STDOUT_FILENO);
	if (temp_cmd_table->num_command == IS_NODE_LAST)
	{
		dup2(shell->fd_out, STDOUT_FILENO);
	}
}
