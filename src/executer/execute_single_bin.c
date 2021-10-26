/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_bin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 01:23:44 by mviudes           #+#    #+#             */
/*   Updated: 2021/10/27 01:23:45 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_final_path(t_shell *shell, t_cmd_table *table)
{
	char	*path;

	path = NULL;
	if (is_absolute_path(table->command))
		path = ft_strdup(table->command);
	else
		path = pathing(table->command, shell->ownenvp);
	return (path);
}

void	execute_single_bin(t_shell *shell, t_cmd_table *table)
{
	char			*path;
	int				ret;
	int				status;

	ret = 0;
	path = NULL;
	path = get_final_path(shell, table);
	shell->pid = fork();
	if (shell->pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (shell->execute == 1)
			ret = execve(path, table->args, shell->ownenvp);
		printf("bash: %s: command not found\n", table->command);
		exit(127);
	}
	free(path);
	wait(&status);
	if (WIFEXITED(status))
		shell->return_value = WEXITSTATUS(status);
	return ;
}
