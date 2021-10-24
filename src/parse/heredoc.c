#include <minishell.h>

void	transf_reading(char **reading, t_shell *shell)
{
	int		i;
	char	*str_aux;
	char	*pdolar;

	if (*reading)
		pdolar = ft_strchr(*reading, '$');
	str_aux = malloc(sizeof(char));
	str_aux[0] = '\0';
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
				str_aux = ft_strjoin(str_aux,
						get_dolar_string(pdolar, &i, shell));
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
	free(*reading);
	*reading = str_aux;
	i = 0;
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
		if(shell->heredoc_value)
			return(1);
		if (ft_strchr(reading, '$') && !(temp->is_union == 1
				|| temp->marks != 0))
			transf_reading(&reading, shell);
		ft_putendl_fd(reading, fd_temp);
		free(reading);
		reading = readline("> ");
	}
	close(fd_temp);
	shell->mode = M_PARSE;
	return (0);
}
