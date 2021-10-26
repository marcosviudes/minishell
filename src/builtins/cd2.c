/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 01:23:20 by mviudes           #+#    #+#             */
/*   Updated: 2021/10/27 01:23:20 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	only_cd(t_shell *shell)
{
	char	**aux;
	char	*content;

	aux = ft_getenvptr("OLDPWD=", shell);
	free(*aux);
	content = ft_getenvcontent("PWD=", shell);
	*aux = ft_strjoin("OLDPWD=", content);
	free(content);
	aux = ft_getenvptr("PWD=", shell);
	free(*aux);
	content = ft_getenvcontent("HOME=", shell);
	*aux = ft_strjoin("PWD=", content);
	chdir(content);
	free(content);
	return (0);
}
