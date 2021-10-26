#include <minishell.h>

void	redir_files_first(t_cmd_table *temp_cmd_table
			, int fd[2], int last_fd[2])
{
	int	outfile;
	int	infile;

	outfile = redirection(temp_cmd_table->outfile);
	infile = indirection(temp_cmd_table->infile);
	(void)last_fd;
	if (temp_cmd_table->outfile)
	{
		dup2(outfile, STDOUT_FILENO);
		close(fd[WRITE_END]);
	}
	if (temp_cmd_table->infile)
	{
		dup2(infile, STDIN_FILENO);
	}
}

void	redir_files_middle(t_cmd_table *temp_cmd_table,
			int fd[2], int last_fd[2])
{
	int	outfile;
	int	infile;

	(void)fd;
	outfile = redirection(temp_cmd_table->outfile);
	infile = indirection(temp_cmd_table->infile);
	if (temp_cmd_table->outfile)
	{
		dup2(outfile, STDOUT_FILENO);
	}
	if (temp_cmd_table->infile)
		close(last_fd[READ_END]);
	dup2(infile, STDIN_FILENO);
}

void	redir_files_last(t_cmd_table *temp_cmd_table, int fd[2], int last_fd[2])
{
	int	outfile;
	int	infile;

	outfile = redirection(temp_cmd_table->outfile);
	infile = indirection(temp_cmd_table->infile);
	if (temp_cmd_table->outfile)
	{
		close(fd[WRITE_END]);
		dup2(outfile, STDOUT_FILENO);
	}
	if (temp_cmd_table->infile)
	{
		close(last_fd[READ_END]);
		dup2(infile, STDIN_FILENO);
	}
}

void	redir_files(t_shell *shell, t_cmd_table *temp_cmd_table,
					int fd[2], int last_fd[2])
{
	int	outfile;
	int	infile;

	outfile = redirection(temp_cmd_table->outfile);
	infile = indirection(temp_cmd_table->infile);
	if (outfile == -1 || infile == -1)
	{
		perror("terminator");
		shell->execute = 0;
		return ;
	}
	if (temp_cmd_table->num_command == IS_NODE_FIRST)
		redir_files_first(temp_cmd_table, fd, last_fd);
	else if (temp_cmd_table->num_command == IS_NODE_LAST)
		redir_files_middle(temp_cmd_table, fd, last_fd);
	else
		redir_files_last(temp_cmd_table, fd, last_fd);
}
