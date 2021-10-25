#include <minishell.h>

int	create_symbol(t_shell *shell, int i)
{
	int		count;
	int		i_aux;
	char	*word;

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
	shell->line_splitted = ft_insert_string(shell->line_splitted, word);
	free(word);
	return (i);
}

static void	create_word2(t_shell *shell, int i, char *word)
{
	if (shell->line[i] != ' ' && (ft_isalnum(shell->line[i])
			|| shell->line[i] == '\'' || shell->line[i] == '\"'))
		shell->union_next = 1;
	else
		shell->union_next = 0;
	shell->line_splitted = ft_insert_string(shell->line_splitted, word);
	free(word);
}

int	create_word(t_shell *shell, int i)
{
	char	*word;
	int		count;
	int		i_aux;

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
	create_word2(shell, i, word);
	return (i);
}

static void	lexical_analyzer2(t_shell *shell, int count, int i)
{
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

void	lexical_analyzer(t_shell *shell)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	lexical_analyzer2(shell, count, i);
}
