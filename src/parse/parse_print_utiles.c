#include <minishell.h>

void	print_redir(void *redir)
{
	t_table_redir	*temp;

	temp = (t_table_redir *)redir;
	if (!temp)
		return ;
	printf("%s-%i\t", temp->file, temp->append);
}

void	print_command(void *cmd)
{
	t_cmd_table	*temp;
	int			i;

	i = 1;
	temp = (t_cmd_table *)cmd;
	if (!temp)
		return ;
	printf("CMD:	%s\n", temp->command);
	if (temp->args)
	{
		while (temp->args[i])
		{
			printf("ARG:	%s\n", temp->args[i]);
			i++;
		}
	}
	printf("OUT: ");
	ft_lstiter(temp->outfile, &print_redir);
	printf("%p \n", temp->outfile);
	printf("IN:  ");
	ft_lstiter(temp->infile, &print_redir);
	printf("%p \n", temp->infile);
	printf("\n");
}
