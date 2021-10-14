#include <minishell.h>

int	double_marks(t_shell *shell, int i)
{
	int		i_aux;
	int		count;
	char	*phrase;
	char	**aux;

	count = 0;
	i_aux = i;
	i_aux++;
	while (shell->line[i_aux] != 34 && shell->line[i_aux] != '\0')
	{
		i_aux++;
		count++;
	}
	if (shell->line[i_aux] == '\0')
		ft_strerror("Quote marks not finished", 1);
	phrase = ft_calloc(sizeof(char), count + 2);
	i_aux = 0;
	while (i_aux <= count)
	{
		phrase[i_aux] = shell->line[i];
		i_aux++;
		i++;
	}
	phrase[i_aux] = 34;
	aux = shell->line_splitted;
	shell->line_splitted = ft_insert_string(shell->line_splitted, phrase);
	ft_free_matrix(aux);
	return (i);
}

int	simple_marks(t_shell *shell, int i)
{
	int		i_aux;
	int		count;
	char	*phrase;
	char	**aux;

	count = 0;
	i_aux = i;
	i_aux++;
	while (shell->line[i_aux] != 39 && shell->line[i_aux] != '\0')
	{
		i_aux++;
		count++;
	}
	if (shell->line[i_aux] == '\0')
		ft_strerror("Quote marks not finished", 1);
	phrase = ft_calloc(sizeof(char), count + 2);
	i_aux = 0;
	while (i_aux <= count)
	{
		phrase[i_aux] = shell->line[i];
		i_aux++;
		i++;
	}
	phrase[i_aux] = 39;
	aux = shell->line_splitted;
	shell->line_splitted = ft_insert_string(shell->line_splitted, phrase);
	ft_free_matrix(aux);
	return (i);
}

int	quotation_marks(t_shell *shell, int i)
{
	if (shell->line[i] == 34)
	{
		i = double_marks(shell, i);
	}
	else
		i = simple_marks(shell, i);
	return (i + 1);
}
