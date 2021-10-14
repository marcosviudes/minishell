#include <minishell.h>

static int	sort_env(void)
{
	int		lines;
	int		i;
	t_sort	*ordered_list;

	i = 0;
	ordered_list = NULL;
	lines = count_lines(g_shell->ownenvp);
	while (i < lines)
	{
		add_line_to_list(g_shell->ownenvp[i], &ordered_list);
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

static void	add_env(char *newenv)
{
	char	*aux2;
	char	**aux;
	int		i;

	i = 0;
	if (!ft_strchr(newenv, '='))
	{
		while (g_shell->ownenvp[i])
		{
			if (ft_strncmp(newenv, g_shell->ownenvp[i], ft_strlen(newenv)) == 0)
				return ;
			i++;
		}
		aux = g_shell->ownenvp;
		g_shell->ownenvp = ft_insert_string(g_shell->ownenvp, newenv);
		ft_free_matrix(aux);
	}
	else
	{
		aux2 = pre_equal(newenv);
		while (g_shell->ownenvp[i])
		{
			if (ft_strncmp(aux2, g_shell->ownenvp[i], ft_strlen(aux2)) == 0)
			{
				free(g_shell->ownenvp[i]);
				g_shell->ownenvp[i] = ft_strdup(newenv);
				return ;
			}
			i++;
		}
		aux = g_shell->ownenvp;
		g_shell->ownenvp = ft_insert_string(g_shell->ownenvp, newenv);
		ft_free_matrix(aux);
	}
}

int	ft_export(char **argv)
{
	int	argc;
	int	i;

	i = 0;
	argc = count_lines(argv);
	if (argc == 0)
		return (sort_env());
	while (i < argc)
	{
		if (ft_isdigit(argv[i][0]))
			printf("export: `%s': not a valid identifier\n", argv[i]);
		else
			add_env(argv[i]);
		i++;
	}
	return (0);
}
