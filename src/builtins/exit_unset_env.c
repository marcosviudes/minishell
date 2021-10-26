#include <minishell.h>

int	ft_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->ownenvp[i])
	{
		printf("%s\n", shell->ownenvp[i]);
		i++;
	}
	return (0);
}

static void	create_newenvp(char *str, t_shell *shell)
{
	char	**table;
	int		i;
	int		j;

	i = 0;
	j = 0;
	table = malloc(sizeof(char *) * (count_lines(shell->ownenvp) + 1));
	while (shell->ownenvp[i + j])
	{
		if (ft_strncmp(str, shell->ownenvp[i + j], (ft_strlen(str))) != 0
			&& !(shell->ownenvp[i + j][ft_strlen(str) + 1] == '\0'
				|| shell->ownenvp[i + j][ft_strlen(str) + 1] == '='))
		{
			table[i] = ft_strdup(shell->ownenvp[i + j]);
			i++;
		}
		else
			j++;
	}
	table[i] = NULL;
	ft_free_matrix(shell->ownenvp);
	shell->ownenvp = table;
}

int	ft_unset(char **argv, t_shell *shell)
{
	int		argc;
	int		i;

	argc = count_lines(argv);
	if (argc == 0)
		return (0);
	i = 0;
	while (i < argc)
	{
		create_newenvp(argv[i], shell);
		i++;
	}
	return (0);
}

static int	is_argument_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i])
	{
		if (!(ft_isdigit(str[i])))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(char **argv, int father)
{
	if (father == 1)
		printf("exit\n");
	if (count_lines(argv) == 0)
		exit(0);
	if (is_argument_numeric(argv[0]) == 0)
	{
		printf("exit: %s: numeric argument required\n", argv[0]);
		exit(255);
	}
	if (count_lines(argv) > 1)
	{
		printf("exit: too many arguments\n");
		return ;
	}
	exit((ft_atoi(argv[0]) % 255));
}
