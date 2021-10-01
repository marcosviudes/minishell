#include <minishell.h>

int	ft_echo(int argc, char **argv)
{
	int i;

	i = 0;
	while (i < argc)
	{
		printf("%s", argv[i]);
		i++;
	}
	write(1, "\n", 1);
	return (0);
}

//cd tiene que recibir argc = 0 si el argv es nulo, si recibe una cadena vacia ("") en argv y argc = 1 no funcionara
//cd solo necesita un argumento.
//pero se puede cambiar.
int	ft_cd(int argc, char **argv, char **envp)
{
	int i;
	char *aux;

	i = 0;
	aux = NULL;
	if (argc == 0)
	{
		chdir("..");
		return (0);
	}
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PWD=", 4))
		{
			aux = ft_substr(envp[i], 4, ft_strlen(envp[i]) - 4);
			aux = ft_strjoin(aux, ft_strjoin("/", argv[0]));
			chdir(aux);
			free(aux);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_pwd(char **envp)
{
	int i;
	char *aux;

	aux = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PWD=", 4))
		{
			aux = ft_substr(envp[i], 4, ft_strlen(envp[i]) - 4);
			printf("%s", aux);
			free(aux);
			return (0);
		}
		i++;
	}
	return (1);
}
