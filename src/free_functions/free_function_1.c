/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_function_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 01:24:29 by mviudes           #+#    #+#             */
/*   Updated: 2021/10/27 01:24:29 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_command(t_shell *shell)
{
	ft_lstclear(&shell->cmd_list, &free_table);
	(void)shell;
}

void	free_all(t_shell *shell)
{
	free(shell);
}

static void	free_info(t_info *info)
{
	if (info->next)
		free_info(info->next);
	free(info->string);
	info->string = NULL;
	free(info);
	info = NULL;
}

static void	free_shell(t_shell *shell)
{
	if (shell->info)
		free_info(shell->info);
	shell->info = NULL;
	free(shell->phrase);
	shell->phrase = NULL;
	ft_free_matrix(shell->line_splitted);
	shell->line_splitted = NULL;
	ft_lstclear(&shell->cmd_list, &free_table);
}

void	frees_function(t_shell *shell)
{
	free_shell(shell);
}
