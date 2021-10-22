#include <minishell.h>

int	create_symbol(t_shell *shell, int i)
{
	int		count;
	int		i_aux;
	char	*word;
	char	**aux;

	if ((shell->line[i] == '<' && shell->line[i + 1] == '<')
		|| (shell->line[i] == '>' && shell->line[i + 1] == '>'))
		i_aux = 2;
	else
		i_aux = 1;
	word = ft_calloc(sizeof(char), i_aux);
	count = 0;
	while (count < i_aux)
	{
		word[count] = shell->line[i];
		count++;
		i++;
	}
	aux = shell->line_splitted;
	shell->line_splitted = ft_insert_string(shell->line_splitted, word);
	free(word);
	ft_free_matrix(aux);
	return (i);
}

int	its_not_special(char digit)
{
	if (digit == ' ' || digit == '<'
		|| digit == '>' || digit == '|'
		|| digit == 34 || digit == 39)
		return (0);
	return (1);
}

int	create_word(t_shell *shell, int i)
{
	char	*word;
	int		count;
	int		i_aux;
	char	**aux;

	i_aux = i;
	count = 0;
	while (its_not_special(shell->line[i_aux])
		&& shell->line[i_aux] != ' ' && shell->line[i_aux] != '\0')
	{
		i_aux++;
		count++;
	}
	word = malloc(sizeof(char) * (count + 1));
	i_aux = 0;
	while (ft_isprint(shell->line[i])
		&& its_not_special(shell->line[i]))
	{
		word[i_aux] = shell->line[i];
		i++;
		i_aux++;
	}
	word[i_aux] = '\0';
	if (shell->line[i] != ' ' && (ft_isalnum(shell->line[i]) || shell->line[i] == '\'' || shell->line[i] == '\"'))
		shell->union_next = 1;
	else
		shell->union_next = 0;
	aux = shell->line_splitted;
	shell->line_splitted = ft_insert_string2(shell->line_splitted, word);
	free(word);
	ft_free_matrix(aux);
	return (i);
}

void	lexical_analyzer(t_shell *shell)
{
	int	i;
	int	count;

	shell->line_splitted = ft_calloc(sizeof(char *), 1);
	shell->info = ft_calloc(sizeof(t_info), 1);
	count = 0;
	i = 0;
	while (shell->line[i])
	{
		if (shell->line[i] == 34 || shell->line[i] == 39)
		{
			i = quotation_marks(shell, i);
			if (i == -1)
				return ;
			add_node(shell, count, 'w');
			count++;
		}
		else if (!its_not_special(shell->line[i]) && shell->line[i] != ' ')
		{
			i = create_symbol(shell, i);
			add_node(shell, count, 's');
			count++;
		}
		else if (ft_isprint(shell->line[i]) && shell->line[i] != ' ')
		{
			i = create_word(shell, i);
			add_node(shell, count, 'w');
			count++;
		}
		else
			i++;
	}
}
