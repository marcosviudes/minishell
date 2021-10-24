#include <minishell.h>

void	parse_symbols(t_shell *shell, t_cmd_table **table, t_info *temp)
{
	t_list	*node;

	if (ft_strncmp(temp->string, ">", 2) == 0)
		shell->flag_redirection = GREAT;
	if (ft_strncmp(temp->string, "<", 2) == 0)
		shell->flag_redirection = LESS;
	if (ft_strncmp(temp->string, ">>", 3) == 0)
		shell->flag_redirection = GREAT_GREAT;
	if (ft_strncmp(temp->string, "<<", 3) == 0)
		shell->flag_redirection = LESS_LESS;
	if (ft_strncmp(temp->string, "|", 2) == 0)
	{
		shell->flag_redirection = 0;
		shell->flag_command = 1;
		node = ft_lstnew(*table);
		ft_lstadd_back(&shell->cmd_list, node);
		*table = ft_calloc(sizeof(t_cmd_table), 1);
	}
}

void	parse_words(t_shell *shell, t_table_redir *temp_redir,
					t_info *temp, t_cmd_table *table)
{
	if (shell->flag_redirection == GREAT
		|| shell->flag_redirection == GREAT_GREAT)
		parse_redirection(shell, temp_redir, temp, table);
	else if (shell->flag_redirection == LESS)
		parse_indirection(shell, temp_redir, temp, table);
	else if (shell->flag_redirection == LESS_LESS)
		parse_heredoc(shell, temp_redir, temp, table);
	else
		parse_command(shell, temp, table);
}

void	parse(t_shell *shell)
{
	t_info			*temp;
	t_cmd_table		*table;
	t_table_redir	*temp_redir;

	temp_redir = NULL;
	shell->cmd_list = NULL;
	shell->flag_command = 1;
	shell->flag_redirection = 0;
	table = NULL;
	temp = shell->info;
	while (temp != NULL)
	{
		if (!table)
			table = ft_calloc(sizeof(t_cmd_table), 1);
		if (temp->type == 's')
			parse_symbols(shell, &table, temp);
		else if (temp->type == 'w')
			parse_words(shell, temp_redir, temp, table);
		if(g_shell->heredoc_value)
			return ;
		temp = temp->next;
	}
	ft_lstadd_back(&shell->cmd_list, ft_lstnew(table));
	return;
	//ft_lstiter(shell->cmd_list, &print_command);
}
