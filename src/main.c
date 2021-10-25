#include <minishell.h>

int	symbol_error(t_info *info)
{
	t_info	*aux;

	aux = info;
	if (aux)
	{
		if (aux->type == 's' && aux->next == NULL)
		{
			printf("bash: syntax error near unexpected token `%s'\n", aux->string);
			return (1);
		}
	}
	while (aux)
	{
		if (aux->type == 's' && aux->next != NULL)
		{
			if (aux->next->type == 's')
			{
				printf("bash: syntax error near unexpected token `%s'\n", aux->string);
				return (1);
			}
		}
		if(aux->type == 's' && aux->next == NULL)
		{
			printf("bash: syntax error near unexpected token `%s'\n", aux->string);
			return (1);
		}
		aux = aux->next;
	}
	return (0);
}

void	loop_shell(t_shell *shell)
{
	t_info	*aux;

	aux = NULL;
	while (TRUE)
	{
		//	//	system("leaks minishell");
		shell->mode = M_READING;
		shell->pid = -1;
		if (shell->line)
			free(shell->line);
		shell->line = NULL;
		signal_init();
		shell->line = readline("terminator$ ");
		if(shell->line == NULL)
			exit(write(1, "exit\n", 5));
		add_history(shell->line);
		if (!shell->line)
			continue ;
		//	//	system("leaks minishell");
		lexical_analyzer(shell);
		//	//	system("leaks minishell");
		if (shell->open_marks != 1 && !symbol_error(shell->info))
		{
	//		//	//	system("leaks minishell");
			shell->open_marks = 0;
			shell->heredoc_value = 0;
//			//	//	system("leaks minishell");
			env_transform(shell);
			//	//	system("leaks minishell");
			arg_unions(shell);
				//	system("leaks minishell");
//			aux = shell->info;
			parse(shell);
			//	//	system("leaks minishell");
			if (shell->heredoc_value == 0)
				execute(shell);
		}
		shell->open_marks = 0;
			//	system("leaks minishell");
		frees_function(shell);
			//	system("leaks minishell");
	}
}

t_shell	*init_structure(t_shell *shell, char **envp)
{
	shell = malloc(sizeof(t_shell));
	shell->heredoc_value = 0;
	shell->phrase = NULL;
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
