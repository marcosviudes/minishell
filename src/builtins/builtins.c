#include <minishell.h>

int	ft_pwd(void)
{
	int i;
	char *aux;

	aux = NULL;
	i = 0;
	while (g_shell->ownenvp[i])
	{
		if (ft_strnstr(g_shell->ownenvp[i], "PWD=", 4))
		{
			aux = ft_substr(g_shell->ownenvp[i], 4, ft_strlen(g_shell->ownenvp[i]) - 4);
			printf("%s\n", aux);
			free(aux);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_echo(char **argv)
{
	int i;
	int	argc;
	int flag;

	flag = 0;
	argc = count_lines(argv);
	i = 0;
	if (ft_strncmp(argv[i], "-n", 2) == 0)
	{
		flag = 1;
		i++;
	}
	while (i < argc)
	{
		printf("%s", argv[i]);
		if (i + 1 != argc)
			printf(" ");
		i++;
	}
	if (flag == 0)
			printf("\n");
	return (0);
}

//cd tiene que recibir argc = 0 si el argv es nulo, si recibe una cadena vacia ("") en argv y argc = 1 no funcionara
//cd solo necesita un argumento.
//pero se puede cambiar.

static void	step_back(char *path)
{
	char	*str;
	int		i;

	str = ft_strrchr(path, '/');
	i = 0;
	while (str[i] != '\0')
	{
		str[i] = '\0';
		i++;
	}
}

int	ft_cd(char **argv)
{
	char	**splitted;
	char	*path;
	char	*oldpwd;
	char	**aux;
	int		i;

	i = 0;
	path = ft_strdup(ft_getenvcontent("PWD="));
	oldpwd = ft_strdup(path);

	if (argv == NULL)
	{
		aux = ft_getenvptr("OLDPWD=");
		free(*aux);
		*aux = ft_strjoin("OLDPWD=", ft_getenvcontent("PWD="));
		aux = ft_getenvptr("PWD=");
		free(*aux);
		*aux = ft_strjoin("PWD=", ft_getenvcontent("HOME="));
		chdir(ft_getenvcontent("HOME="));
		return (0);
	}
	splitted = ft_split(argv[0], '/');
	i = 0;
	while (splitted[i])
	{
		if (ft_strncmp(splitted[i], "..", 2) == 0 && ft_strlen(splitted[i]) == 2)
			step_back(path);
		else
			ft_strjoin(ft_strjoinchar(path, '/'), splitted[i]);
		i++;
	}
	i = 0;
	if (access(path, F_OK) == 0)
	{
		while (g_shell->ownenvp[i] && path != NULL)
		{
			if (ft_strncmp(g_shell->ownenvp[i], "OLDPWD=", 7) == 0)
			{
				free(g_shell->ownenvp[i]);
				g_shell->ownenvp[i] = ft_strjoin("OLDPWD=", oldpwd);
			}
			if (ft_strncmp(g_shell->ownenvp[i], "PWD=", 4) == 0)
			{
				free(g_shell->ownenvp[i]);
				g_shell->ownenvp[i] = ft_strjoin("PWD=", path);
			}
			i++;
		}
		chdir(path);
	}
	else
		printf("cd: no such file or directory\n");
	return (0);
}	
