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
	{
		shell->open_marks = 1;
		printf("Open quotation marks\n");
		return (-1);
	}
	phrase = malloc(sizeof(char) * (count + 3));
	i_aux = 0;
	while (i_aux <= count)
	{
		phrase[i_aux] = shell->line[i];
		i_aux++;
		i++;
	}
	phrase[i_aux++] = 34;
	phrase[i_aux] = '\0';
	if (shell->line[i + 1] != ' ' && (ft_isalnum(shell->line[i + 1])
			|| shell->line[i + 1] == '\'' || shell->line[i + 1] == '\"'))
		shell->union_next = 1;
	else
		shell->union_next = 0;
	aux = shell->line_splitted;
	shell->line_splitted = ft_insert_string(shell->line_splitted, phrase);
	ft_free_matrix(aux);
	free(phrase);
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
	{
		shell->open_marks = 1;
		printf("Open quotation marks\n");
		return (-1);
	}
	phrase = ft_calloc(sizeof(char), count + 2);
	i_aux = 0;
	while (i_aux <= count)
	{
		phrase[i_aux] = shell->line[i];
		i_aux++;
		i++;
	}
	phrase[i_aux] = 39;
	if (shell->line[i + 1] != ' ' && (ft_isalnum(shell->line[i + 1])
			|| shell->line[i + 1] == '\'' || shell->line[i + 1] == '\"'))
		shell->union_next = 1;
	else
		shell->union_next = 0;
	aux = shell->line_splitted;
	shell->line_splitted = ft_insert_string(shell->line_splitted, phrase);
	ft_free_matrix(aux);
	return (i);
}

int	quotation_marks(t_shell *shell, int i)
{
	shell->open_marks = 0;
	if (shell->line[i] == 34)
		i = double_marks(shell, i);
	else
		i = simple_marks(shell, i);
	if (shell->open_marks == 1)
		return (-1);
	return (i + 1);
}
