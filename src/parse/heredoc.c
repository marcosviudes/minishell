#include <minishell.h>

void	transf_reading(char **reading, t_shell *shell)
{
	int		i;
	char	*finalstring;
	char	*pdolar;

	if (*reading)
		pdolar = ft_strchr(*reading, '$');
	finalstring = malloc(sizeof(char));
	finalstring[0] = '\0';
	i = 0;
	while (i < (int)ft_strlen(*reading))
	{
		if (reading[0][i] == '$')
		{
			if (reading[0][i + 1] == '?')
			{
				finalstring = ft_strjoin(finalstring,
						ft_itoa(shell->return_value));
				pdolar = ft_strchr(pdolar + 1, '$');
				i++;
			}
			else
			{
				finalstring = ft_strjoin(finalstring,
						get_dolar_string(pdolar, &i, shell));
				pdolar = ft_strchr(pdolar + 1, '$');
			}
			i++;
		}
		else
		{
			finalstring = ft_strjoinchar(finalstring, (reading[0][i]));
			i++;
		}
	}
	free(*reading);
	*reading = finalstring;
	i = 0;
}

void	ft_heredoc(t_shell *shell, t_info *temp)
{
	char	*reading;
	int		fd_temp;

	shell->heredoc_buff = malloc(sizeof(char *));
	shell->heredoc_buff[0] = "";
	fd_temp = open(".tempheredoc", O_WRONLY | O_CREAT | O_APPEND | O_TRUNC, S_IRWXU);
	reading = readline("> ");
	while (!(ft_strncmp(reading, temp->string, ft_strlen(temp->string)) == 0))
	{
		if (ft_strchr(reading, '$') && !(temp->is_union == 1|| temp->marks != 0))
			transf_reading(&reading, shell);
		ft_putendl_fd(reading, fd_temp);
		free(reading);
		reading = readline("> ");
	}
	close(fd_temp);
	//La funcion que controla los heredocs
	//debera utilizar lo que hay dentro de .tempheredoc y usarlo como entrada.
}
