#include <minishell.h>

int	ft_pwd(void)
{
	int		i;
	char	*aux;

	aux = NULL;
	i = 0;
	while (g_shell->ownenvp[i])
	{
		if (ft_strnstr(g_shell->ownenvp[i], "PWD=", 4))
		{
			aux = ft_substr(g_shell->ownenvp[i],
					4, ft_strlen(g_shell->ownenvp[i]) - 4);
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
	int	i;
	int	argc;
	int	flag;

	flag = 0;
	argc = count_lines(argv);
	if (argc == 0)
		return(printf("\n"));
	i = 0;
	if (ft_strncmp(argv[i], "-n", 3) == 0)
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
