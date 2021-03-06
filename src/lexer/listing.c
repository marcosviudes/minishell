/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 01:24:48 by mviudes           #+#    #+#             */
/*   Updated: 2021/10/27 01:24:49 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	new = malloc(sizeof(t_info));
	if (!new)
		return ;
	new->type = car;
	new->marks = get_marks(shell->line_splitted[i]);
	new->string = get_string(shell->line_splitted[i], new->marks);
	new->union_next = shell->union_next;
	new->is_union = 0;
	new->next = NULL;
	count = 0;
	if (shell->info == NULL)
		shell->info = new;
	else
	{
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = new;
	}
}
