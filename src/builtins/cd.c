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
			free(ret);
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

	if (*argv == NULL)
		return (only_cd(shell));
	oldpwd = ft_getenvcontent("PWD=", shell);
	path = get_path(oldpwd, argv[0]);
	return (ft_chdir(path, oldpwd, shell));
}
