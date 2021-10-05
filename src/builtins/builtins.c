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

	argc = count_lines(argv);
	i = 0;
	while (i < argc)
	{
		printf("%s\n", argv[i]);
		i++;
	}
	return (0);
}

//cd tiene que recibir argc = 0 si el argv es nulo, si recibe una cadena vacia ("") en argv y argc = 1 no funcionara
//cd solo necesita un argumento.
//pero se puede cambiar.
/*
int	ft_cd(char **argv)
{
	int i;
	char *aux;
	int	argc;

	argc = count_lines(argv);
	i = 0;
	aux = NULL;
	if (argc == 0)
	{
		chdir("..");
		return (0);
	}
	while (g_shell->ownenvp[i])
	{
		if (ft_strnstr(g_shell->ownenvp[i], "PWD=", 4))
		{
			aux = ft_substr(g_shell->ownenvp[i], 4, ft_strlen(g_shell->ownenvp[i]) - 4);
			aux = ft_strjoin(aux, ft_strjoin("/", argv[0]));
			chdir(aux);
			free(aux);
			return (0);
		}
		i++;
	}
	return (1);
}
*/
