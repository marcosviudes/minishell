/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 01:22:59 by mviudes           #+#    #+#             */
/*   Updated: 2021/10/27 01:22:59 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	loop_shell_2(t_shell *shell)
{
	shell->open_marks = 0;
	shell->heredoc_value = 0;
	env_transform(shell);
	arg_unions(shell);
	parse(shell);
	if (shell->heredoc_value == 0)
		execute(shell);
}

void	loop_shell(t_shell *shell)
{
	while (TRUE)
	{
		shell->mode = M_READING;
		shell->pid = -1;
		if (shell->line)
			free(shell->line);
		shell->line = NULL;
		signal_init();
		shell->line = readline("terminator$ ");
		if (shell->line == NULL)
			exit(write(1, "exit\n", 5));
		add_history(shell->line);
		if (!shell->line)
			continue ;
		lexical_analyzer(shell);
		if (shell->open_marks != 1 && !symbol_error(shell->info, shell))
			loop_shell_2(shell);
		shell->open_marks = 0;
		frees_function(shell);
	}
}

t_shell	*init_structure(t_shell *shell, char **envp)
{
	shell = malloc(sizeof(t_shell));
	shell->heredoc_value = 0;
	shell->phrase = ft_strdup("");
	shell->finalstring = NULL;
	shell->pdolar = NULL;
	shell->flag_heredoc_file = 0;
	shell->mode = M_READING;
	shell->open_marks = 0;
	shell->ownenvp = fill_env(envp);
	shell->flag_command = 0;
	shell->flag_redirection = 0;
	shell->prompt_len = 0;
	shell->line_splitted = NULL;
	shell->pdolar = NULL;
	shell->return_value = 0;
	shell->line = NULL;
	shell->num_of_pipes = 0;
	shell->pdolar = NULL;
	shell->union_next = 0;
	shell->cmd_list = NULL;
	shell->info = NULL;
	return (shell);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	shell = NULL;
	shell = init_structure(shell, envp);
	g_shell = shell;
	loop_shell(shell);
	return (0);
}
