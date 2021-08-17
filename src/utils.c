#include <minishell.h>

char	**ft_insert_string(char **table, char *str)
{
	int		i;
	char	**aux;

	i = 0;
	while (table[i] != NULL)
		i++;
	aux = ft_calloc(sizeof(char *), i);
	i = 0;
	while (table[i] != NULL)
	{
		aux[i] = ft_strdup(table[i]);
		i++;
	}
	aux[i] = str;
	ft_free_matrix(table);
	return (aux);
}

void	ft_free_matrix(char **matrix)
{
	int	i;

	i = -1;
	while (matrix[++i])
		free (matrix[i]);
	free (matrix);
}
