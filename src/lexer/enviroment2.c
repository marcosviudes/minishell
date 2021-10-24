#include <minishell.h>

static char	*final_phrase(char *phrase, int len)
{
	char	*end_game;
	int		i;

	end_game = ft_calloc(sizeof(char), (ft_strlen(phrase) - len + 1));
	i = 0;
	len++;
	while (phrase[i + len])
	{
		end_game[i] = phrase[i + len];
		i++;
	}
	return (end_game);
}

static char	*converse(char *str, int *count, t_shell *shell)
{
	int		i;
	char	*ret;
	char	*aux;

	aux = ft_strjoin(str, "=");
	ret = NULL;
	i = 0;
	while (shell->ownenvp[i])
	{
		if (ft_strnstr(shell->ownenvp[i], aux, ft_strlen(aux)))
		{
			ret = final_phrase(shell->ownenvp[i], ft_strlen(str));
			*count = *count + (ft_strlen(str));
			return (ret);
		}
		i++;
	}
	ret = ft_strdup("");
	*count = *count + ft_strlen(aux);
	return (ret);
}

char	*get_dolar_string(char *pdolar, int *count, t_shell *shell)
{
	char	*var;
	char	*aux;
	int		i;
	int		j;

	i = 0;
	j = 0;
	aux = ft_strtrim(pdolar, "$");
	while (ft_isalnum(aux[i]))
		i++;
	var = malloc(sizeof(char) * (i + 1));
	while (j < i)
	{
		var[j] = aux[j];
		j++;
	}
	var[j] = '\0';
	free(aux);
	aux = converse(var, count, shell);
	free(var);
	return (aux);
}
