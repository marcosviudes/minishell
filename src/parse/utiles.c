#include <minishell.h>

char	**ft_insert_string2(char **table, char *str)
{
	int		i;
	char	**aux;

	i = 0;
	if (!str)
		return (table);
	if (!table)
		return (ft_calloc(sizeof(char **), 1));
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
