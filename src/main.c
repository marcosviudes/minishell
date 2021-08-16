#include <minishell.h>
#include <curses.h>
#include <term.h>

void	free_all(t_shell *shell)
{
	free(shell->prompt);
	free(shell);
}

t_shell	*init_structure(t_shell *shell)
{
	shell = malloc(sizeof(t_shell));
	//init_tercaps(shell);
	return(shell);
}

void	loop_shell(t_shell *shell)
{
	while (1)
	{
		shell->line = readline("terminator$ ");
		add_history(shell->line);
		//lexical_analyze(shell);
		//parse(shell);
		//execute(shell);
	}
}

int	main(int argc, char **argv)
{
	t_shell	*shell;
	
	(void)argc;
	(void)argv;
	shell = NULL;
	shell = init_structure(shell); 
	loop_shell(shell);
	free_all(shell);
	system("leaks minishell");
	return (0);
}
