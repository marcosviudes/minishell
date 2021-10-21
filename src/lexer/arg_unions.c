#include <minishell.h>

void	go_union(t_info *list)		//tenemos el nodo 0 (list)
{
	t_info	*aux;
	char	*word;

	aux = list->next;												//cogemos en aux el nodo 1
	word = list->string;
	list->string = ft_strjoin(list->string, aux->string);			//ponemos en el nodo 0 la union de los strings
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
	/*
	while (aux != NULL)
	{
		printf("String: %s\n", aux->string);
		printf("Type:   %c\n", aux->type);
		printf("Marks:  %i\n", aux->marks);
		printf("--------------------------------\n");
		printf("================================\n");
		aux = aux->next;
	}
	*/
	aux = list;
	while (list->next != NULL)
	{
		if (list->union_next == 1)
			go_union(list);
		else
			list = list->next;
	}
}
