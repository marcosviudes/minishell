#include <minishell.h>

static void	env_transform3(t_shell *shell, t_info *aux, int *i)
{
	if (aux->string[*i + 1] == '?')
	{
		shell->finalstring = ft_strjoin(shell->finalstring,
				ft_itoa(shell->return_value));
		shell->pdolar = ft_strchr(shell->pdolar + 1, '$');
		(*i)++;
	}
	else if (aux->string[*i + 1] == ' '
		|| aux->string[*i + 1] == '\0')
	{
		shell->finalstring = ft_strjoinchar(shell->finalstring, '$');
		shell->pdolar = ft_strchr(shell->pdolar + 1, '$');
		(*i)++;
	}
	else
	{
		shell->finalstring = ft_strjoin(shell->finalstring,
				get_dolar_string(shell->pdolar, i, shell));
		shell->pdolar = ft_strchr(shell->pdolar + 1, '$');
	}
	(*i)++;
}

static void	env_transform2(t_info *aux, t_shell *shell)
{
	int	i;
	char *aux;

	i = 0;
	while (i < (int)ft_strlen(aux->string))
	{
		if (aux->string[i] == '$' && aux->marks != 2)
		{
			env_transform3(shell, aux, &i);
		}
		else
		{
			aux = shell->finalstring;
			shell->finalstring = ft_strjoinchar(shell->finalstring,
					aux->string[i]);
			free(aux);
			i++;
		}
	}
}

void	env_transform(t_shell *shell)
{
	t_info	*aux;

	aux = shell->info;
	while (aux != NULL && aux->string != NULL)
	{
		if (aux->string)
			shell->pdolar = ft_strchr(aux->string, '$');
		shell->finalstring = malloc(sizeof(char));
		shell->finalstring[0] = '\0';
		env_transform2(aux, shell);
		free(aux->string);
		aux->string = shell->finalstring;
		aux = aux->next;
	}
}
