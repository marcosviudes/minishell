/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 01:23:51 by mviudes           #+#    #+#             */
/*   Updated: 2021/10/27 01:23:52 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	isbuiltin(char *string)
{
	if (ft_strncmp(string, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(string, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(string, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(string, "export", 7) == 0)
		return (1);
	if (ft_strncmp(string, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(string, "env", 4) == 0)
		return (1);
	if (ft_strncmp(string, "exit", 5) == 0)
		return (1);
	return (0);
}

void	execute_builtin(t_cmd_table *temp, char *command, t_shell *shell)
{
	if (ft_strncmp(command, "echo", 5) == 0)
		shell->return_value = ft_echo(&temp->args[1]);
	if (ft_strncmp(command, "cd", 3) == 0)
		shell->return_value = ft_cd(&temp->args[1], shell);
	if (ft_strncmp(command, "pwd", 4) == 0)
		shell->return_value = ft_pwd(shell);
	if (ft_strncmp(command, "export", 7) == 0)
		shell->return_value = ft_export(&temp->args[1], shell);
	if (ft_strncmp(command, "unset", 5) == 0)
		shell->return_value = ft_unset(&temp->args[1], shell);
	if (ft_strncmp(command, "env", 3) == 0)
		shell->return_value = ft_env(shell);
	if (ft_strncmp(command, "exit", 4) == 0)
		ft_exit(&temp->args[1], 1);
}
