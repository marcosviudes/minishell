#include <minishell.h>
# include <term.h>

void	read_stdin(t_shell *shell)
{
	char	buff[BUFSIZE + 1];
	int		read_ret;
	int		i;

	i = 0;
	buff[BUFSIZE] =  '\0';
	
	shell->line = malloc(200);
	shell->line[199] = '\0';
	shell->read_bytes = 0;
	read_ret = 0;
	while(ft_strncmp(buff, "\n", 2) != 0)
	{
		read_ret = read(STDIN_FILENO, buff, BUFSIZE);
		write(2, buff, ft_strlen(buff));
		buff[read_ret] = '\0';
		shell->read_bytes += read_ret;
//		write(STDERR_FILENO, buff, ft_strlen(buff));
//			ft_strlcpy(shell->line, buff, ft_strlen(buff));
//		ft_putstr_fd(buff, 2);
		if (!ft_isprint(buff[0]))
				tercaps(buff, shell);
		else
			write(STDOUT_FILENO, buff, ft_strlen(buff));
		shell->line = ft_memcpy(shell->line, buff, ft_strlen(buff));
//		shell->line[shell->read_bytes] = buff[0];
//		buff[shell->read_bytes + 1] = '\0';
		//write(STDOUT_FILENO, buff, shell->read_bytes);
	}
//	write(2, buff , ft_strlen(buff));
//	write(2, shell->line , ft_strlen(shell->line));
	ft_bzero(buff, BUFFER_SIZE);
}
