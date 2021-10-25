#include <minishell.h>

static int	sort_env(t_shell *shell)
{
	int		len;
	int		i;
	t_sort	*ordered_list;

	i = 0;
	ordered_list = NULL;
	len = count_lines(shell->ownenvp);
	while (i < len)
	{
		add_line_to_list(shell->ownenvp[i], &ordered_list);
		i++;
	}
	sort_list(ordered_list);
	print_order_list(ordered_list);
	free_list(ordered_list);
	return (0);
}

static char	*pre_equal(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	while (str[i] != '=')
		i++;
	ret = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] != '=')
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

static void	add_env_else(t_shell *shell, char *newenv, int i)
{
	char	*aux2;

	aux2 = pre_equal(newenv);
	while (shell->ownenvp[i])
	{
		if (ft_strncmp(aux2, shell->ownenvp[i], ft_strlen(aux2)) == 0)
		{
			free(shell->ownenvp[i]);
			shell->ownenvp[i] = ft_strdup(newenv);
			return ;
		}
		i++;
	}
	shell->ownenvp = ft_insert_string(shell->ownenvp, newenv);
}

static void	add_env(char *newenv, t_shell *shell)
{
	int		i;

	i = 0;
	if (!ft_strchr(newenv, '='))
	{
		while (shell->ownenvp[i])
		{
			if (ft_strncmp(newenv, shell->ownenvp[i], ft_strlen(newenv)) == 0)
				return ;
			i++;
		}
		shell->ownenvp = ft_insert_string(shell->ownenvp, newenv);
	}
	else
		add_env_else(shell, newenv, i);
}

int	ft_export(char **argv, t_shell *shell)
{
	int	argc;
	int	i;

	i = 0;
	argc = count_lines(argv);
	if (argc == 0)
		return (sort_env(shell));
	while (i < argc)
	{
		if (ft_isdigit(argv[i][0]))
		{
			printf("export: `%s': not a valid identifier\n", argv[i]);
			return (1);
		}
		else
			add_env(argv[i], shell);
		i++;
	}
	return (0);
}
