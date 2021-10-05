#include <minishell.h>
#include <curses.h>
#include <term.h>

void	free_all(t_shell *shell)
{
	free(shell->prompt);
	free(shell);
}

void	execute(t_shell *shell)
{
	t_cmd_table *temp;

	temp = shell->cmd_list->content;
	if (ft_strncmp("export", temp->command, 6) == 0)
		ft_export(temp->args);
	if (ft_strncmp("env", temp->command, 3) == 0)
		ft_env(temp->args);
}

void	loop_shell(t_shell *shell)
{
	int i;
	t_info *aux;

	while (TRUE)
	{
		signal_init();
		shell->line = readline("terminator$ ");
		add_history(shell->line);
		lexical_analyzer(shell);
		env_transform(shell);
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
	while(j < i)
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
	return(shell);
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
