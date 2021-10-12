#include <minishell.h>

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new;

	if (!ptr)
		return (malloc(size));
	if (size == 0)
		return (ptr);
	new = malloc(size);
	ft_memcpy(new, ptr, size);
	free(ptr);
	return (new);
}

char	**ft_insert_string2(char **table, char *str)
{
	int		i;
	char	**aux;

	i = 0;
	if(!str)
		return(table);
	if(!table)
		return(ft_calloc(sizeof(char**),1));
	while (table[i] != NULL)
		i++;
	aux = ft_calloc(sizeof(char *), i + 2);
	i = 0;
	while (table[i] != NULL)
	{
		aux[i] = ft_strdup(table[i]);
		i++;
	}
	aux[i] = ft_strdup(str);
	return (aux);
}

/**
 *	ls
 *	-la
 *  |
 * wc
 */

void	print_redir(void *redir)
{
	t_table_redir *temp;
	
	temp = (t_table_redir*)redir;
	if(!temp)
		return;
	printf("%s-%i\t", temp->file, temp->append);
}

void	print_command(void *cmd)
{
	t_cmd_table *temp;
	int			i;

	i = 0;
	temp = (t_cmd_table*)cmd;
	if(!temp)
		return;
	printf("CMD:	%s\n", temp->command);
	if(temp->args)
		while(temp->args[i])
		{
			printf("ARG:	%s\n", temp->args[i]);
			i++;
		}
	printf("OUT: ");
	ft_lstiter(temp->outfile, &print_redir);
	printf("%p \n", temp->outfile);
	printf("IN:  ");
	ft_lstiter(temp->infile, &print_redir);
	printf("%p \n", temp->infile);
}

void	info_free(t_info *info)
{
	while(info->next != NULL)
		info_free(info);
	if(info->string)
		free(info->string);
	free(info);
}

/*void	info_add_prev(t_info **info)
{
	t_info	*temp;
	t_info 	*aux;

	temp = NULL;
	aux = *info;
	while(*info != NULL)
	{
		(*info)->prev = temp;
		temp = *info;
		*info = (*info)->next;
	}
	*info = aux;
}*/

void	info_add_prev(t_info *info)
{
	t_info	*temp;
	t_info 	*aux;

	temp = NULL;
	aux = info;
	while(info != NULL)
	{
		info->prev = temp;
		temp = info;
		info = info->next;
	}
	info = aux;
}

void print_list(t_info *info)
{
	printf("\n");
	while(info != NULL)
	{
		printf("%p: string = %-8s\tprev = %-16p\tnext = %-p\n"
				,info, info->string, info->prev, info->next);
		info = info->next;
	}
}

void free_table(void *arg)
{
	t_cmd_table *table;

	if(arg == NULL)
	{
		free(arg);
		return;
	}
	table = (t_cmd_table*) arg;
	free(table->command);
	ft_free_matrix(table->args);
	free(table->outfile);
	free(table->infile);
	free(table); 
}

void	free_info_list(t_info *info)
{
	if(info->next)
		free_info_list(info->next);
	free(info->string);
	free(info);
}

void	parse(t_shell *shell)
{
	t_list		*node;
	t_info		*temp;
	t_cmd_table	*table;
	t_table_redir	*temp_redir;
	int			command_flag;
	int			redirection_flag;

	shell->cmd_list = NULL;
	command_flag = 1;
	redirection_flag = 0;
	table = NULL;
	temp = shell->info;
	info_add_prev(shell->info);
	print_list(shell->info);
	printf("\n");
	while(temp != NULL)
	{
		if(!table)
			table = ft_calloc(sizeof(t_cmd_table), 1);
		if(temp->type == 's')
		{
			if(ft_strncmp(temp->string, ">", 2) == 0)
				redirection_flag = GREAT;
			if(ft_strncmp(temp->string, "<", 2) == 0)
				redirection_flag = LESS;
			if(ft_strncmp(temp->string, ">>", 3) == 0)
				redirection_flag = GREAT_GREAT;
			if(ft_strncmp(temp->string, "<<", 3) == 0)
				redirection_flag = LESS_LESS;
			if(ft_strncmp(temp->string, "|", 2) == 0)
			{
				redirection_flag = 0;
				command_flag = 1;
				node = ft_lstnew(table);
				ft_lstadd_back(&shell->cmd_list, node);
				table = ft_calloc(sizeof(t_cmd_table), 1);
			}
		}
		else if(temp->type == 'w')
		{/*
			if(table->command == NULL && command_flag  == 1 && !redirection_flag)
			{
				table->command = ft_strdup(temp->string);
				command_flag = 0;
			}*/
			if(redirection_flag == GREAT || redirection_flag == GREAT_GREAT)
			{
				temp_redir = malloc(sizeof(t_table_redir));
				temp_redir->file = ft_strdup(temp->string);
				temp_redir->append = APPEND_OFF;
				if(redirection_flag == GREAT_GREAT)
					temp_redir->append = APPEND_ON;
				redirection_flag = 0;
				ft_lstadd_back(&table->outfile, ft_lstnew(temp_redir));
			}
			else if(redirection_flag == LESS)
			{
				temp_redir = malloc(sizeof(t_table_redir));
				temp_redir->file = ft_strdup(temp->string);
				temp_redir->append = APPEND_OFF;
				redirection_flag = 0;
				ft_lstadd_back(&table->infile, ft_lstnew(temp_redir));
			}
			else
			{
				if(table->command == NULL && command_flag  == 1 && !redirection_flag)
				{
					table->command = ft_strdup(temp->string);
					command_flag = 0;
				}
				if(!table->args)
					table->args = ft_calloc(sizeof(char**), 1);
				table->args = ft_insert_string2(table->args, temp->string);
			}
		}
		temp = temp->next;
	}
	node = ft_lstnew(table);
	ft_lstadd_back(&shell->cmd_list, node);
	ft_lstiter(shell->cmd_list, &print_command);
//	ft_lstclear(&shell->cmd_list, &free_table);
//	free_info_list(shell->info);
//	printf("hola\n");
}
