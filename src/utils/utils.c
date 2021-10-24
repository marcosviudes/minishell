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
	if (!matrix)
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

int	count_lines(char **table)
{
	int	i;

	i = 0;
	if (!table)
		return (0);
	while (table[i])
		i++;
	return (i);
}
