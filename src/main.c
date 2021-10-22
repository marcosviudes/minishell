#include <minishell.h>
#include <curses.h>
#include <term.h>

void	free_all(t_shell *shell)
{
	free(shell->prompt);
	free(shell);
}

static void	loop_shell2(t_shell *shell, t_info *aux)
{
	env_transform(shell);
	arg_unions(shell);
	aux = shell->info;
	ft_free_matrix(shell->line_splitted);
	parse(shell);
	execute(shell);
}

void	loop_shell(t_shell *shell)
{
	t_info	*aux;

	aux = NULL;
	while (TRUE)
	{
		if (shell->line)
			free(shell->line);
		shell->line = NULL;
		signal_init();
		shell->line = readline("terminator$ ");
		add_history(shell->line);
		if (!shell->line)
			continue ;
		lexical_analyzer(shell);
		if (shell->open_marks == 1)
		{
			shell->open_marks = 0;
			printf("Error: Quotation marks not closed.\n");
			continue ;
		}
		loop_shell2(shell, aux);
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
