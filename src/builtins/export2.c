#include <minishell.h>

static char	*add_marks(char *newenv)
{
	char	*ret;
	int		i;

	ret = malloc(sizeof(char) * ft_strlen(newenv) + 3);
	i = 0;
	while (newenv[i] != '=')
	{
		ret[i] = newenv[i];
		i++;
	}
	ret[i] = newenv[i];
	i++;
	ret[i++] = 34;
	while (newenv[i - 1])
	{
		ret[i] = newenv[i - 1];
		i++;
	}
	ret[i++] = 34;
	ret[i] = '\0';
	return (ret);
}

void	add_line_to_list(char *line, t_sort **ordered_list)
{
	t_sort	*aux;
	char	*aux2;

	aux = *ordered_list;
	if (!*ordered_list)
	{
		aux = ft_calloc(sizeof(t_sort), 1);
		aux->next = NULL;
		*ordered_list = aux;
	}
	else
	{
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = ft_calloc(sizeof(t_sort), 1);
		if (ft_strchr(line, '='))
		{
			aux2 = add_marks(line);
			aux->line = ft_strdup(aux2);
			free(aux2);
		}
		else
			aux->next->line = ft_strdup(line);
		aux->next->next = NULL;
	}
}

void	free_list(t_sort *list)
{
	t_sort	*aux;

	if(list->next)
		free_list(list->next);
	free(list->line);
	free(list);
}

void	print_order_list(t_sort *list)
{
	t_sort	*aux;

	aux = list;
	while (aux)
	{
		printf("%s\n", aux->line);
		aux = aux->next;
	}
}

void	sort_list(t_sort *list)
{
	t_sort	*aux;
	char	*aux2;
	int		flag;

	flag = 0;
	aux2 = NULL;
	while (flag == 0)
	{
		aux = list;
		flag = 1;
		while (aux->next->line != NULL)
		{
			if (aux->next && (ft_strncmp(aux->line,
						aux->next->line, ft_strlen(aux->line)) > 0))
			{
				aux2 = aux->next->line;
				aux->next->line = aux->line;
				aux->line = aux2;
				flag = 0;
			}
			aux = aux->next;
		}
	}
}
