#include <minishell.h>

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
/*
static void	free_info(t_shell *shell)
{
	t_info *aux;

	aux = shell->info;
	while (aux)
	{
		free(aux->string);
		aux->string = NULL;
		if (shell->info->next != NULL)
		{
			shell->info = shell->info->next;
			free(aux);
			aux = NULL;
			aux = shell->info;
		}
		else
			free(aux);
			aux = NULL;
	}
}*/

static void	free_info(t_info *info)
{
	if (info->next)
		free_info(info->next);
	free(info->string);
	info->string = NULL;
	free(info);
	info = NULL;
}

static void free_shell(t_shell *shell)
{
	//	system("leaks minishell");
	free_info(shell->info);
	shell->info = NULL;
	//	system("leaks minishell");
	free(shell->phrase);
	shell->phrase = NULL;
	//	system("leaks minishell");
	ft_free_matrix(shell->line_splitted);
	shell->line_splitted = NULL;
	//	//	system("leaks minishell");
	ft_lstclear(&shell->cmd_list, &free_table);
	//	system("leaks minishell");
}

void	frees_function(t_shell *shell)
{
	//free(shell->line);
	//free(shell->line_splitted);
	free_shell(shell);
}
