#include <minishell.h>

void	double_marks2(t_shell *shell, int *i_aux, int *count, int *i)
{
	while (shell->line[*i_aux] != 34 && shell->line[*i_aux] != '\0')
	{
		(*i_aux)++;
		(*count)++;
	}
	if (shell->line[*i_aux] == '\0')
	{
		shell->open_marks = 1;
		printf("Open quotation marks\n");
		return ;
	}
	free(shell->phrase);
	shell->phrase = ft_calloc(sizeof(char), *count + 2);
	(*i_aux) = 0;
	while (*i_aux <= *count)
	{
		shell->phrase[*i_aux] = shell->line[*i];
		(*i_aux)++;
		(*i)++;
	}
	shell->phrase[*i_aux] = 34;
}

int	double_marks(t_shell *shell, int i)
{
	int		i_aux;
	int		count;

	count = 0;
	i_aux = i;
	i_aux++;
	double_marks2(shell, &i_aux, &count, &i);
	if (shell->open_marks == 1)
		return (-1);
	if (shell->line[i + 1] != ' ' && (ft_isalnum(shell->line[i + 1])
			|| shell->line[i + 1] == '\'' || shell->line[i + 1] == '\"'))
		shell->union_next = 1;
	else
		shell->union_next = 0;
	shell->line_splitted = ft_insert_string(shell->line_splitted,
			shell->phrase);
	return (i);
}

void	simple_marks2(t_shell *shell, int *i_aux, int *count, int *i)
{
	while (shell->line[*i_aux] != 39 && shell->line[*i_aux] != '\0')
	{
		(*i_aux)++;
		(*count)++;
	}
	if (shell->line[*i_aux] == '\0')
	{
		shell->open_marks = 1;
		printf("Open quotation marks\n");
		return ;
	}
	free(shell->phrase);
	shell->phrase = ft_calloc(sizeof(char), *count + 2);
	(*i_aux) = 0;
	while (*i_aux <= *count)
	{
		shell->phrase[*i_aux] = shell->line[*i];
		(*i_aux)++;
		(*i)++;
	}
	shell->phrase[*i_aux] = 39;
}

int	simple_marks(t_shell *shell, int i)
{
	int		i_aux;
	int		count;

	count = 0;
	i_aux = i;
	i_aux++;
	simple_marks2(shell, &i_aux, &count, &i);
	if (shell->open_marks == 1)
		return (-1);
	if (shell->line[i + 1] != ' ' && (ft_isalnum(shell->line[i + 1])
			|| shell->line[i + 1] == '\'' || shell->line[i + 1] == '\"'))
		shell->union_next = 1;
	else
		shell->union_next = 0;
	shell->line_splitted = ft_insert_string(shell->line_splitted,
			shell->phrase);
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
