#include <minishell.h>

int	its_not_special(char digit)
{
	if (digit == ' ' || digit == '<' 
		|| digit == '>' || digit == '=' 
		|| digit == 34 || digit == 39)
		return (0);
	return (1);
}

int	 create_word(t_shell *shell, int i)
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
	word = ft_calloc(sizeof(char), count);
	i_aux = 0;
	while (ft_isprint(shell->line[i])
		&& its_not_special(shell->line[i]))
	{
		word[i_aux] = shell->line[i];
		i++;
		i_aux++;
	}
	aux = shell->line_splitted;
	shell->line_splitted = ft_insert_string(shell->line_splitted, word);
	ft_free_matrix(aux);
	return (i);
}

void	lexical_analyzer(t_shell *shell)
{
	int i;

	shell->line_splitted = ft_calloc(sizeof(char *), 1);
	i = 0;
	while (shell->line[i])
	{
		if (shell->line[i] == 34 || shell->line[i] == 39)
			i = quotation_marks(shell, i);
		else if (ft_isprint(shell->line[i])
			&& shell->line[i] != ' ')
			i = create_word(shell, i);
		else
			i++;
		//if (ft_isprint(shell->line[i])
		//	&& !its_not_special(shell->line[i]))
			//i = create_symbol(shell, i);
	}
	//lexycal_errors();
}
