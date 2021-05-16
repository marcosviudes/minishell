/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 21:57:07 by mviudes           #+#    #+#             */
/*   Updated: 2021/05/16 21:30:43 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	prompt_config(t_shell *shell, char *prompt_str)
{
	int		len;

	len = ft_strlen(prompt_str);
	shell->prompt_len = len;
	shell->prompt = ft_calloc(1, shell->prompt_len + 1);
	if (!shell->prompt)
		return ;
	ft_strlcpy(shell->prompt, prompt_str, len + 1 );
}

void	prompt_put(t_shell *shell)
{
	write(1, shell->prompt, shell->prompt_len);
}
