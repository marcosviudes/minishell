#include <minishell.h>

char *transf_reading_bucle(char **reading, char *str_aux, char *pdolar, t_shell *shell)
{
	int	i;
	char	*aux;
	i = 0;
	while (i < (int)ft_strlen(*reading))
	{
		if (reading[0][i] == '$')
		{
			if (reading[0][i + 1] == '?')
			{
				str_aux = ft_strjoin(str_aux,
						ft_itoa(shell->return_value));
				pdolar = ft_strchr(pdolar + 1, '$');
				i++;
			}
			else
			{
				aux = get_dolar_string(pdolar, &i, shell);
				str_aux = ft_strjoin(str_aux, aux);
				free(aux);
				pdolar = ft_strchr(pdolar + 1, '$');
			}
			i++;
		}
		else
		{
			str_aux = ft_strjoinchar(str_aux, (reading[0][i]));
			i++;
		}
	}
	return (str_aux);
}

void	transf_reading(char **reading, t_shell *shell)
{
	char	*str_aux;
	char	*pdolar;
	char	*aux;

	pdolar = NULL;
	if (*reading)
		pdolar = ft_strchr(*reading, '$');
	str_aux = malloc(sizeof(char));
	str_aux[0] = '\0';
	aux = transf_reading_bucle(reading, str_aux, pdolar, shell);
	free(*reading);
	free(str_aux);
	*reading = aux;
}

int	ft_heredoc(t_shell *shell, t_info *temp)
{
	char	*reading;
	int		fd_temp;

	shell->mode = M_HEREDOC;
	shell->heredoc_value = 0;
	fd_temp = open(".tempheredoc", O_WRONLY | O_CREAT
			| O_APPEND | O_TRUNC, S_IRWXU);
	reading = readline("> ");
	while (reading && !(ft_strncmp(reading,
				temp->string, ft_strlen(temp->string)) == 0))
	{
		if (shell->heredoc_value)
			return (1);
		if (ft_strchr(reading, '$') && !(temp->is_union == 1
				|| temp->marks != 0))
			transf_reading(&reading, shell);
		ft_putendl_fd(reading, fd_temp);
		free(reading);
		reading = readline("> ");
	}
	free(reading);
	close(fd_temp);
	shell->mode = M_PARSE;
	return (0);
}
