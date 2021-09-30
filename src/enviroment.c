#include <minishell.h>

static char *final_phrase(char *phrase, int len)
{
	char *end_game;
	int i;

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

static char *converse(char *str, char **envp, int *count)
{
	int i;
	char *ret;
	char *aux;

	aux = ft_strjoin(str, "=");
	ret = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], aux, ft_strlen(aux)))
		{
			ret = final_phrase(envp[i], ft_strlen(str));
			*count = *count + (ft_strlen(str));
			return (ret);
		}
		i++;
	}
	ret = ft_strjoin("$", str);
	*count = *count + ft_strlen(ret);
	return (ret);
}

static char	*get_dolar_string(char *pdolar, char **envp, int *count)
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
	while(j < i)
	{
		var[j] = aux[j];
		j++;
	}
	var[j] = '\0';
	free(aux);
	aux = converse(var, envp, count);
	free(var);
	return (aux);
}

void	env_transform(t_shell *shell, char **envp)
{
	t_info *aux;
	char	*pdolar;
	char	*finalstring;
	int		i;

	aux = shell->info;
	i = 0;
	while (aux != NULL && aux->string != NULL)
	{
		if (aux->string)
			pdolar = ft_strchr(aux->string, '$');
		finalstring =  malloc(sizeof(char));
		finalstring[0] = '\0';
		while (i < (int)ft_strlen(aux->string))
		{
			if (aux->string[i] == '$' && aux->marks != 2)
			{
				finalstring = ft_strjoin(finalstring, get_dolar_string(pdolar, envp, &i));
				pdolar = ft_strchr(pdolar + 1, '$');
				i++;
			}
			else
			{
				finalstring = ft_strjoinchar(finalstring, (aux->string[i]));
				i++;
			}
		}
		i = 0;
		free(aux->string);
		aux->string = finalstring;
		aux = aux->next;
	}
}
