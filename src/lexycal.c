#include <minishell.h>

int	create_word(t_shell *shell, int i)
{
	char	*word;
	int		count;
	int		i_aux;

	i_aux = i;
	count = 0;
	while (ft_isalnum(shell->line[i_aux]))
	{
		i_aux++;
		count++;
	}
	word = ft_calloc(sizeof(char), count);
	i_aux = 0;
	while (ft_isalnum(shell->line[i]))
	{
		word[i_aux] = shell->line[i];
		i++;
		i_aux++;
	}
	shell->line_splitted = ft_insert_string(shell->line_splitted, word);
	return (i);
}

void	lexical_analyzer(t_shell *shell)
{
	int i;

	shell->line_splitted = malloc(sizeof(char *));
	i = 0;
	while (shell->line[i])
	{
		if (ft_isalnum(shell->line[i]))
			i = create_word(shell, i);
		i++;
	}
	//lexycal_errors();
}
