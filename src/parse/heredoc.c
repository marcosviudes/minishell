#include <minishell.h>

void	ft_heredoc(t_shell *shell, char *str)
{
	char	*reading;
	int		fd_temp;

	reading = malloc(sizeof(char));
	shell->heredoc_buff = malloc(sizeof(char *));
	shell->heredoc_buff[0] = "";
	fd_temp = open(".tempheredoc", O_WRONLY | O_CREAT | O_APPEND | O_TRUNC, S_IRWXU);
	while (!(ft_strncmp(reading, str, ft_strlen(str)) == 0))
	{
		free(reading);
		reading = readline("> ");
		ft_putendl_fd(reading, fd_temp);
	}
	close(fd_temp);
	//La funcion que controla los heredocs
	//debera utilizar lo que hay dentro de .tempheredoc y usarlo como entrada.
}
