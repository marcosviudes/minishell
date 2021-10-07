#include <minishell.h>

char	**ft_insert_string(char **table, char *str)
{
	int		i;
	char	**aux;

	i = 0;
	while (table[i] != NULL)
		i++;
	aux = ft_calloc(sizeof(char *), i + 2);
	i = 0;
	while (table[i] != NULL)
	{
		aux[i] = ft_strdup(table[i]);
		i++;
	}
	aux[i] = ft_strdup(str);
	return (aux);
}

void	ft_free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if(!matrix)
	{
		free(matrix);
		return ;
	}
	while (matrix[i])
		i++;
	while (i >= 0)
	{
		free(matrix[i]);
		i--;
	}
	free(matrix);
}

void	ft_strerror(char *str, int num)
{
	ft_putstr_fd(str, 1);
	exit(num);
}

int	count_lines(char **table)
{
	int i;

	i = 0;
	if (!table)
		return (0);
	while(table[i])
		i++;
	return (i);
}

char	*ft_getenvcontent(char *header)
{
	int		i;
	char	*ret;

	i = 0;
	while (g_shell->ownenvp[i])
	{
		if (ft_strncmp(g_shell->ownenvp[i], header, ft_strlen(header)) == 0)
		{
			ret = ft_substr(g_shell->ownenvp[i], ft_strlen(header), ft_strlen(g_shell->ownenvp[i]) - ft_strlen(header));
			return (ret);
		}
		i++;
	}
	return (NULL);
}

char	**ft_getenvptr(char *header)
{
	int		i;
	char	**ret;

	i = 0;
	while (g_shell->ownenvp[i])
	{
		if (ft_strncmp(g_shell->ownenvp[i], header, ft_strlen(header)) == 0)
		{
			ret = &g_shell->ownenvp[i];
			return (ret);
		}
		i++;
	}
	return (NULL);
}

char	*ft_getenvcpy(char *header)
{
	int		i;
	char	*ret;

	i = 0;
	while (g_shell->ownenvp[i])
	{
		if (ft_strncmp(g_shell->ownenvp[i], header, ft_strlen(header)) == 0)
		{
			ret = ft_strdup(g_shell->ownenvp[i]);
			return (ret);
		}
		i++;
	}
	return (NULL);
}