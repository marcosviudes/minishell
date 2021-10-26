#include <minishell.h>
#include <termios.h>

void redirfds(int i, int num_commands, int fd[2], int last_fd[2], t_shell *shell)
{
	if (i != 0)
	{
		close(last_fd[WRITE_END]);
		dup2(last_fd[READ_END], STDIN_FILENO);
	}
	if (i < num_commands)
		dup2(fd[WRITE_END], STDOUT_FILENO);
	if (i == num_commands)
		dup2(shell->fd_out, STDOUT_FILENO);
}

void child_process(t_shell *shell, t_cmd_table *temp_cmd_table, char *path)
{
	int	ret;

	if (isbuiltin(temp_cmd_table->command))
	{
		execute_builtin(temp_cmd_table , temp_cmd_table->command, shell);
		exit(0);
	}
	signal(SIGQUIT, SIG_DFL);
	ret = execve(path, temp_cmd_table->args, shell->ownenvp);
	printf("bash: %s: command not found\n", temp_cmd_table->command);
	exit(127);
}

void	redir_files(t_cmd_table *temp_cmd_table, int fd[2], int last_fd[2], int i, int num_commands)
{

	int	outfile;
	int	infile;

	outfile = redirection(temp_cmd_table->outfile);
	infile = indirection(temp_cmd_table->infile);
	if (i == 0)
	{
		if (temp_cmd_table->outfile)
		{
			dup2(outfile, STDOUT_FILENO);
			close(fd[WRITE_END]);
		}
		if (temp_cmd_table->infile){
			dup2(infile , STDIN_FILENO);
		}
	}
	if (i == num_commands)
	{
		if (temp_cmd_table->outfile){
			dup2(outfile, STDOUT_FILENO);
		}
		if (temp_cmd_table->infile)
			close(last_fd[READ_END]);
		dup2(infile , STDIN_FILENO);
	}
	else
	{
		if (temp_cmd_table->outfile)
		{
			close(fd[WRITE_END]);
			dup2(outfile, STDOUT_FILENO);
		}
		if (temp_cmd_table->infile)
		{
			close(last_fd[READ_END]);
			dup2(infile , STDIN_FILENO);
		}
	}
	
		
}

void execute_commands_single(t_shell *shell)
{
	t_cmd_table *temp_cmd_table;
	int	outfile;
	int	infile;

	temp_cmd_table = (t_cmd_table *)shell->cmd_list->content;
	outfile = redirection(temp_cmd_table->outfile);
	infile = indirection(temp_cmd_table->infile);
	if (outfile == -1 || infile == -1)
		{
			perror("terminator");
			return;
		}
	if (!temp_cmd_table->command){
		if (outfile != STDOUT_FILENO)
			close(outfile);
		return ;
	}
	dup2(outfile, STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	if (temp_cmd_table->command && isbuiltin(temp_cmd_table->command))
		execute_builtin(temp_cmd_table, temp_cmd_table->command, shell);
	else
		execute_single_bin(shell, temp_cmd_table);
}

void	wait_for_childs(t_shell *shell, int num_commands)
{
	int	status;
	int	i;

	i = 0;
	while (i < num_commands + 1)
	{
		wait(&status);
		if (WIFEXITED(status))
			shell->return_value = WEXITSTATUS(status);
		i++;
	}
}

void execute_commands_multiple(t_shell *shell, int num_commands)
{
	int		i;
	char	*path;
	int		fd[2];
	int		last_fd[2];

	t_cmd_table *temp_cmd_table;
	t_list *temp_node = shell->cmd_list;

	i = 0;
	num_commands--;

	while (temp_node)
	{
		temp_cmd_table = (t_cmd_table*)temp_node->content;
		path = get_final_path(shell, temp_cmd_table);
		pipe(fd);
		redirfds(i, num_commands, fd, last_fd, shell);
		redir_files(temp_cmd_table, fd, last_fd, i, num_commands);
		shell->pid = fork();
		if (shell->pid == 0){
			signal(SIGQUIT, SIG_DFL);
			child_process(shell, temp_cmd_table, path);
		}
		last_fd[READ_END] = fd[READ_END];
		last_fd[WRITE_END] = fd[WRITE_END];

		fd[READ_END] = 0;
		fd[WRITE_END] = 1;

		temp_node = temp_node->next;
		free(path);
		i++;
	}
	wait_for_childs(shell, num_commands);
	close(last_fd[READ_END]);
	close(last_fd[WRITE_END]);
	close(fd[READ_END]);
	close(fd[WRITE_END]);
}

void execute(t_shell *shell)
{
	int			num_commands;
	t_cmd_table *temp_cmd_table;
	struct	termios	old;
	tcgetattr(0, &old);
	
	shell->mode = M_EXECUTE;
	shell->fd_in = dup(STDIN_FILENO);
	shell->fd_out = dup(STDOUT_FILENO);
	num_commands = ft_lstsize(shell->cmd_list);
	temp_cmd_table = NULL;
	if (num_commands == 1)
		execute_commands_single(shell);
	else
		execute_commands_multiple(shell, num_commands);
	dup2(shell->fd_out, STDOUT_FILENO);
	dup2(shell->fd_in, STDIN_FILENO);
	close(shell->fd_out);
	close(shell->fd_in);
	if (shell->flag_heredoc_file)
		unlink(".tempheredoc");
	shell->flag_heredoc_file = 0;
	tcsetattr(0, TCSANOW, &old);
}
