/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 01:23:06 by mviudes           #+#    #+#             */
/*   Updated: 2021/10/27 01:23:07 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	step_back(char *path)
{
	char	*str;
	int		i;

	str = ft_strrchr(path, '/');
	if (!str)
		return ;
	i = 0;
	while (str[i] != '\0')
	{
		str[i] = '\0';
		i++;
	}
}

static char	*get_path(char *oldpwd, char *arg)
{
	char	**splitted;
	char	*ret;
	char	*aux;
	int		i;

	ret = ft_strdup(oldpwd);
	splitted = ft_split(arg, '/');
	i = 0;
	while (splitted[i])
	{
		if (ft_strncmp(splitted[i], "..", 2) == 0
			&& ft_strlen(splitted[i]) == 2)
			step_back(ret);
		else if (!(ft_strncmp(splitted[i], ".", 2) == 0))
		{
			aux = ft_strjoinchar(ret, '/');
			ret = aux;
			ret = ft_strjoin(aux, splitted[i]);
			free(aux);
		}
		i++;
	}
	ft_free_matrix(splitted);
	return (ret);
}

static void	change_env(char *oldpwd, char *path, t_shell *shell, int i)
{
	if (ft_strncmp(shell->ownenvp[i], "OLDPWD=", 7) == 0)
	{
		free(shell->ownenvp[i]);
		shell->ownenvp[i] = ft_strjoin("OLDPWD=", oldpwd);
	}
	if (ft_strncmp(shell->ownenvp[i], "PWD=", 4) == 0)
	{
		free(shell->ownenvp[i]);
		shell->ownenvp[i] = ft_strjoin("PWD=", path);
	}
}

static int	ft_chdir(char *path, char *oldpwd, t_shell *shell)
{
	int	i;

	i = 0;
	if (access(path, F_OK) == 0)
	{
		while (shell->ownenvp[i] && path != NULL)
		{
			change_env(oldpwd, path, shell, i);
			i++;
		}
		chdir(path);
		return (0);
	}
	else
	{
		printf("cd: no such file or directory\n");
		return (1);
	}
}

int	ft_cd(char **argv, t_shell *shell)
{
	char	*path;
	char	*oldpwd;
	int		ret;

	if (*argv == NULL)
	{
		ret = only_cd(shell);
		return (ret);
	}
	oldpwd = ft_getenvcontent("PWD=", shell);
	if (argv[0][0] == '/')
		path = ft_strdup(argv[0]);
	else
		path = get_path(oldpwd, argv[0]);
	ret = ft_chdir(path, oldpwd, shell);
	free(path);
	free(oldpwd);
	return (ret);
}
