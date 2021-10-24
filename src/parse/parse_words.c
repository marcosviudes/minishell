#include <minishell.h>

void	parse_redirection(t_shell *shell, t_table_redir *temp_redir,
						t_info *temp, t_cmd_table *table)
{
	temp_redir = ft_calloc(sizeof(t_table_redir), 1);
	temp_redir->file = ft_strdup(temp->string);
	temp_redir->append = APPEND_OFF;
	if (shell->flag_redirection == GREAT_GREAT)
		temp_redir->append = APPEND_ON;
	shell->flag_redirection = 0;
	ft_lstadd_back(&table->outfile, ft_lstnew(temp_redir));
}

void	parse_indirection(t_shell *shell, t_table_redir *temp_redir,
						t_info *temp, t_cmd_table *table)
{
	temp_redir = ft_calloc(sizeof(t_table_redir), 1);
	temp_redir->file = ft_strdup(temp->string);
	temp_redir->append = APPEND_OFF;
	shell->flag_redirection = 0;
	ft_lstadd_back(&table->infile, ft_lstnew(temp_redir));
}

void	parse_command(t_shell *shell, t_info *temp, t_cmd_table *table)
{


	if (table->command == NULL && shell->flag_command
		== 1 && !shell->flag_redirection)
	{
		table->command = ft_strdup(temp->string);
		shell->flag_command = 0;
	}
	if (!table->args)
		table->args = ft_calloc(sizeof(char **), 1);
	char **aux;
	aux = table->args;
	table->args = ft_insert_string2(table->args, temp->string);
	ft_free_matrix(aux);
}

void	parse_heredoc(t_shell *shell, t_table_redir *temp_redir,
						t_info *temp, t_cmd_table *table)
{
	temp_redir = ft_calloc(sizeof(t_table_redir), 1);
	temp_redir->file = ft_strdup(".tempheredoc");
	temp_redir->append = APPEND_OFF;
	shell->flag_redirection = 0;
	ft_lstadd_back(&table->infile, ft_lstnew(temp_redir));
	ft_heredoc(shell, temp);
}
