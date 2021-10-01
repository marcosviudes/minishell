#include <minishell.h>
#include <curses.h>
#include <term.h>

t_shell *g_shell;

void	free_all(t_shell *shell)
{
	free(shell->prompt);
	free(shell);
}

t_shell	*init_structure(t_shell *shell)
{
	shell = malloc(sizeof(t_shell));

	return(shell);
}

void	loop_shell(t_shell *shell, char **envp)
{
	int i;
	t_info *aux;

	while (TRUE)
	{
		signal_init();
		shell->line = readline("terminator$ ");
		add_history(shell->line);
		lexical_analyzer(shell);
		env_transform(shell, envp);
		aux = shell->info;
		i = 0;
		free(shell->line_splitted);
		while (aux != NULL)
		{
			printf("String: %s\n", aux->string);
			printf("Type:   %c\n", aux->type);
			printf("Marks:  %i\n", aux->marks);
			printf("--------------------------------\n");
			aux = aux->next;
		}
		
		//parse(shell);
		//execute(shell);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	
	(void)argc;
	(void)argv;
	shell = NULL;
	shell = init_structure(shell);
	g_shell = shell;
	loop_shell(shell, envp);
	free_all(shell);
	system("leaks minishell");
	return (0);
}
