#include <minishell.h>

int	ft_pwd(t_shell *shell)
{
	int		i;
	char	*aux;

	aux = NULL;
	i = 0;
	while (shell->ownenvp[i])
	{
		if (ft_strnstr(shell->ownenvp[i], "PWD=", 4))
		{
			aux = ft_substr(shell->ownenvp[i],
					4, ft_strlen(shell->ownenvp[i]) - 4);
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
		return (printf("\n"));
	i = 0;
	if (ft_strncmp(argv[i], "-n", 3) == 0)
	{
		flag = 1;
		i++;
	}
	while (i < argc)
	{
		ft_putstr_fd(argv[i], 1);
		if (i + 1 != argc)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (flag == 0)
		ft_putchar_fd('\n', 1);
	return (0);
}
