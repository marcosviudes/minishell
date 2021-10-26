/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 01:25:33 by mviudes           #+#    #+#             */
/*   Updated: 2021/10/27 01:25:33 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	symbol_error2(t_info *aux)
{
	while (aux)
	{
		if (aux->type == 's' && aux->next != NULL)
		{
			if (aux->next->type == 's')
			{
				printf("bash: syntax error near unexpected token `%s'\n",
					aux->string);
				return (1);
			}
		}
		if (aux->type == 's' && aux->next == NULL)
		{
			printf("bash: syntax error near unexpected token `%s'\n",
				aux->string);
			return (1);
		}
		aux = aux->next;
	}
	return (0);
}

int	symbol_error(t_info *info, t_shell *shell)
{
	t_info	*aux;
	int		i;
	int		ret;

	aux = info;
	if (aux)
	{
		if (aux->type == 's' && aux->next == NULL)
		{
			printf("bash: syntax error near unexpected token `%s'\n",
				aux->string);
			return (1);
		}
	}
	ret = symbol_error2(aux);
	if (ret == 1)
		return (1);
	i = 0;
	while (shell->line[i] == ' ' || shell->line[i] == '\t'
		|| shell->line[i] == '\n' || shell->line[i] == '\v'
		|| shell->line[i] == '\f' || shell->line[i] == '\r')
		i++;
	if (shell->line[i] == '\0')
		return (1);
	return (0);
}
