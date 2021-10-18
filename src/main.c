#include <minishell.h>
#include <curses.h>
#include <term.h>

void	free_all(t_shell *shell)
{
	free(shell->prompt);
	free(shell);
}

void	loop_shell(t_shell *shell)
{
	int		i;
	t_info	*aux;
//	char	**oldpwd;

//	oldpwd = malloc(sizeof(char *));
//	oldpwd[0] = ft_strjoin("OLDPWD=", ft_getenvcontent("PWD="));
//	ft_export(oldpwd);
	while (TRUE)
	{
		if (shell->line)
			free(shell->line);
		shell->line = NULL;
		signal_init();
		//system("leaks minishell");
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
		env_transform(shell);
		arg_unions(shell);
		aux = shell->info;
		i = 0;
		ft_free_matrix(shell->line_splitted);
		//DEBUG LEXYCAL + ENV
		/*
		while (aux != NULL)
		{
			printf("String: %s\n", aux->string);
			printf("Type:   %c\n", aux->type);
			printf("Marks:  %i\n", aux->marks);
			printf("--------------------------------\n");
			aux = aux->next;
		}
		*/
		parse(shell);
		execute(shell);
	}
}

char	**fill_env(char **envp)
{
	char	**new_envp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 1));
	while (j < i)
	{
		new_envp[j] = ft_strdup(envp[j]);
		j++;
	}
	new_envp[j] = NULL;
	return (new_envp);
}

t_shell	*init_structure(t_shell *shell, char **envp)
{
	shell = malloc(sizeof(t_shell));
	shell->ownenvp = fill_env(envp);
	shell->condition = 0;
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
