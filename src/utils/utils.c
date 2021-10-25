#include <minishell.h>

char	**ft_insert_string(char **table, char *str)
{
	int		i;
	char	**aux;
	int		j;

	i = 0;
	j = 0;
	aux = NULL;
	if (table == NULL)
	{
		table = malloc(sizeof(char *) * 2);
		table[0] = ft_strdup(str);
		table[1] = NULL;
		return (table);
	}
	else
	{
		while (table[i] != NULL)
			i++;
		aux = malloc(sizeof(char *) * (i + 2));
		while (j < i)
		{
			aux[j] = ft_strdup(table[j]);
			j++;
		}
		aux[j] = ft_strdup(str);
		j++;
		aux[j] = NULL;
		ft_free_matrix(table);
		return (aux);
	}
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
