#include <minishell.h>

int	get_marks(char *string)
{
	if (string[0] == 34)
		return (1);
	else if (string[0] == 39)
		return (2);
	else
		return (0);
}

char	*get_string(char *string, int flag)
{
	char	*ret;

	if (flag == 0)
		ret = ft_strdup(string);
	else if (flag == 1)
		ret = ft_strtrim(string, "\"");
	else
		ret = ft_strtrim(string, "\'");
	return (ret);
}

void	add_node(t_shell *shell, int i, char car)
{
	int		count;
	t_info	*new;
	t_info	*aux;

	aux = shell->info;
	new = ft_calloc(sizeof(t_info), 1);
	new->type = car;
	new->marks = get_marks(shell->line_splitted[i]);
	new->string = get_string(shell->line_splitted[i], new->marks);
	new->union_next = shell->union_next;
	new->is_union = 0;
	new->next = NULL;
	count = 0;
	if (aux)
		while (aux->next != NULL)
			aux = aux->next;
	if (aux->string == NULL)
		aux = ft_memcpy(aux, new, sizeof(t_info));
	else
	{
		aux->next = ft_calloc(sizeof(t_info), 1);
		aux->next = ft_memcpy(aux->next, new, sizeof(t_info));
	}
	free(new);
}
