#include <minishell.h>

void	go_union(t_info *list)
{
	t_info	*aux;
	char	*word;

	aux = list->next;
	word = list->string;
	list->string = ft_strjoin(list->string,
			aux->string);
	free(word);
	list->next = aux->next;
	if (aux->next != NULL)
		aux->next->prev = list;
	list->union_next = aux->union_next;
	list->is_union = 1;
	free(aux->string);
	free(aux);
}

void	arg_unions(t_shell *shell)
{
	t_info	*list;
	t_info	*aux;

	list = shell->info;
	aux = list;
	aux = list;
	if (list == NULL)
		return ;
	while (list->next != NULL)
	{
		if (list->union_next == 1)
			go_union(list);
		else
			list = list->next;
	}
}
