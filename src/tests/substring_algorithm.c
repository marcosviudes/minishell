#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <minishell.h>

void	print_tab(int **matrix, int x, int y)
{
	int	i;
	int	j;

	j = 0;
	while (j < y)
	{
		i = 0;
		while (i < x)
		{
			//printf("%i ", matrix[j][i]);
			i++;
		}
		//printf("\n");
		j++;
	}
	//printf("\n");
}

int	**allocate_int_matrix(int x, int y)
{
	int	**ret;

	ret = ft_calloc(y, sizeof(int *));
	while (y--)
		ret[y] = ft_calloc(x, sizeof(int));
	return (ret);
}

int	ft_max(int x, int y)
{
	return (x ^ ((x ^ y) & -(x < y)));
}

/*
 * The function returns the number off letters that mach
 * in two strings
 */

int	substring_algorithm(int **matrix, char *to_find, char *string)
{
	int	i;
	int	j;

	j = ft_strlen(string);
	while (j >= 0)
	{
		i = ft_strlen(to_find) - 1;
		while (i >= 0)
		{
			if (to_find[i] == string[j])
				matrix[j][i] = matrix[j + 1][i + 1] + 1;
			else
				matrix[j][i] = ft_max(matrix[j + 1][i], matrix[j][i + 1]);
			i--;
		}
		j--;
	}
	print_tab(matrix, ft_strlen(to_find), ft_strlen(string));
	return (matrix[0][0]);
}

/*
 * The function return a pointer to the most similar srtring
 * to to_find in the multiple strings pointer.
 */

char	*common_substring(char **strings, char *to_find)
{
	int		ret;
	int		**matrix;
	int		count;
	int		old_count;
	int		i;

	i = 0;
	old_count = 0;
	if (!to_find || *strings == NULL || !strings || to_find[0] == '\0')
		return (NULL);
	while (*strings[i] != '\0')
	{
		matrix = allocate_int_matrix(ft_strlen(to_find) + 2,
				ft_strlen(strings[i]) + 2);
		count = substring_algorithm(matrix, to_find, strings[i]);
		if (count > old_count)
		{
			ret = i;
			old_count = count;
		}
		free(matrix);
		i++;
	}
	return (strings[ret]);
}

int	main(int argc, char **argv)
{
	char	*ret;
	char	*strings[6];

	strings[0] = "echo";
	strings[1] = "pwd";
	strings[2] = "export";
	strings[3] = "unset";
	strings[4] = "env";
	strings[5] = "exit";
	ret = common_substring(strings, argv[1]);
	printf("the most similar string is %s\n", ret);
	return (0);
}
