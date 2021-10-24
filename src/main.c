#include <minishell.h>
#include <curses.h>
#include <term.h>

void	free_command(t_shell *shell)
{
	ft_lstclear(&shell->cmd_list, &free_table);
	(void)shell;
}

void	free_all(t_shell *shell)
{
	//free(shell->prompt);
	free(shell);
}

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
		system("leaks minishell");
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
		lexical_analyzer(shell);
		system("leaks minishell");
		if (shell->open_marks != 1 && !symbol_error(shell->info))
		{
			system("leaks minishell");
			env_transform(shell);
			system("leaks minishell");
			arg_unions(shell);
			system("leaks minishell");
			aux = shell->info;
			parse(shell);
			system("leaks minishell");
			execute(shell);
			system("leaks minishell");
		}
		shell->open_marks = 0;
	}
}

t_shell	*init_structure(t_shell *shell, char **envp)
{
	shell = malloc(sizeof(t_shell));
	shell->ownenvp = fill_env(envp);
	shell->return_value = 0;
	shell->line = NULL;
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
	free_all(shell);
	return (0);
}
