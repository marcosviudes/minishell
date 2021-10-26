#include <minishell.h>

void	fd_copy_restore(int fd[2], int last_fd[2])
{
	last_fd[READ_END] = fd[READ_END];
	last_fd[WRITE_END] = fd[WRITE_END];
	fd[READ_END] = 0;
	fd[WRITE_END] = 1;
}

void	fd_close(int fd[2], int last_fd[2])
{
	close(last_fd[READ_END]);
	close(last_fd[WRITE_END]);
	close(fd[READ_END]);
	close(fd[WRITE_END]);
}

void	fd_default_restore(t_shell *shell)
{
	dup2(shell->fd_out, STDOUT_FILENO);
	dup2(shell->fd_in, STDIN_FILENO);
	close(shell->fd_out);
	close(shell->fd_in);
}
