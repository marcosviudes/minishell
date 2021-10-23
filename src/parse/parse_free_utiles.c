#include <minishell.h>

void	free_info_list(t_info *info)
{
	if (info->next)
		free_info_list(info->next);
	free(info->string);
	free(info);
}

void	free_table_redir(void *arg)
{
	t_table_redir	*table;

	if (arg == NULL)
	{
		free(arg);
		return ;
	}
	table = (t_table_redir *)arg;
	free(table->file);
	free(table);
}

void	free_table(void *arg)
{
	t_cmd_table	*table;

	if (arg == NULL)
	{
		free(arg);
		return ;
	}
	table = (t_cmd_table *)arg;
	free(table->command);
	ft_free_matrix(table->args);
	ft_lstclear(&table->outfile, &free_table_redir);
	ft_lstclear(&table->infile, &free_table_redir);
	free(table);
}

void	info_free(t_info *info)
{
	while (info->next != NULL)
		info_free(info);
	if (info->string)
		free(info->string);
	free(info);
}
