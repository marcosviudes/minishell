#include <minishell.h>

int	is_absolute_path(char *command)
{
	if (*command == '/' || *command == '.')
		if (access(command, X_OK | F_OK) == 0)
			return (1);
	return (0);
}
int	isbuiltin(char *string)
{
	if (ft_strncmp(string, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(string, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(string, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(string, "export", 7) == 0)
		return (1);
	if (ft_strncmp(string, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(string, "env", 4) == 0)
		return (1);
	if (ft_strncmp(string, "exit", 5) == 0)
		return (1);
	return (0);
}

void	execute_builtin(t_cmd_table *temp, char *command)
{
	if (ft_strncmp(command, "echo", 5) == 0)
		g_shell->condition = ft_echo(&temp->args[1]);
	if (ft_strncmp(command, "cd", 3) == 0)
		g_shell->condition = ft_cd(&temp->args[1]);
	if (ft_strncmp(command, "pwd", 4) == 0)
		g_shell->condition = ft_pwd();
	if (ft_strncmp(command, "export", 7) == 0)
		g_shell->condition = ft_export(&temp->args[1]);
	if (ft_strncmp(command,"unset", 5) == 0)
		g_shell->condition = ft_unset(&temp->args[1]);
	if (ft_strncmp(command,"env", 3) == 0)
		g_shell->condition = ft_env();
	if (ft_strncmp(command,"exit", 4) == 0)
		ft_exit(&temp->args[1], 1);
}

int	open_file(char *file_name, int mode)
{
	if(access(file_name, F_OK ) == 0 && access(file_name, R_OK | W_OK) != 0)
		return(-1);
	if(mode == APPEND_ON)
		return(open(file_name, O_APPEND | O_WRONLY | O_CREAT, 00644));
	else
		return(open(file_name, O_TRUNC | O_WRONLY | O_CREAT, 00644));
	
}

int	search_for_line(char **envp)
{
	int		i;
	char	*cosa;

	i = 0;
	while (envp[i])
	{
		cosa = ft_strnstr(envp[i], "PATH=", 5);
		if (cosa != NULL)
			return (i);
		i++;
	}
	return (-1);
}

char	*pathing(char *command, char **envp)
{
	char	*the_path;
	char	**paths;
	int		i;
	int		fd;

	the_path = NULL;
	paths = ft_split(envp[search_for_line(envp)], ':');
	paths[0] = ft_strchr(paths[0], '/');
	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		paths[i] = ft_strjoin(paths[i], command);
		fd = open(paths[i], O_RDONLY);
		if (fd >= 0)
		{
			the_path = ft_strdup(paths[i]);
			ft_free_matrix(paths);
			close(fd);
			return (the_path);
		}
		i++;
	}
	ft_free_matrix(paths);
	return (NULL);
}



int	redirection(t_list *redir)
{
	t_table_redir redir_table;
	int		fd;
	int		i;

	i = 0;
	if (redir)
	{
		while (redir)
		{
			redir_table = *(t_table_redir*)redir->content;
			if (i > 0)
				close(fd);
			fd = open_file(redir_table.file, redir_table.append);
			if (fd == -1)
				return (1);
			i++;
			redir = redir->next;
		}
		return (fd);
	}
	return(STDOUT_FILENO);
}

int	indirection(t_list *redir)
{
	t_table_redir redir_table;
	int		fd;
	int		i;

	i = 0;
	if(redir) 
	{
		while(redir)
		{
			redir_table = *(t_table_redir*)redir->content;
			if(i > 0)
				close(fd);
			if(access(redir_table.file, F_OK ) == 0 && access(redir_table.file, R_OK | W_OK) != 0)
				return(-1);
			fd = open(redir_table.file, O_RDWR , 00644);
			if(fd == -1)
				return(1);
			i++;
			redir = redir->next;
		}
		return(fd);
	}
	return(STDIN_FILENO);
}

void execute_single_bin(t_shell *shell, t_cmd_table *table)
{
	char	*path;
	pid_t	pid;
	int		error;

	error = 0;
	path = NULL;
	//printf("--------%s\n", table->command);
	if (is_absolute_path(table->command))
		path = table->command;
	else
		path = pathing(table->command, shell->ownenvp);
	//printf("%s\n", path);
	if (!path)
		return ;
	pid = fork();
	if(pid == 0){
		execve(path, table->args, shell->ownenvp);

	}
	shell->pid = pid;
	wait(&shell->pid);
	return ;
}
void redirfds(int i, int num_commands, int fd[2], int last_fd[2], t_shell *shell)
{
	if(i != 0)
	{
		close(last_fd[WRITE_END]);
		dup2(last_fd[READ_END], STDIN_FILENO);
	}
	if(i < num_commands)
	{
		//close(fd[READ_END]);
		//fprintf(stderr, ">---------%d\n", fd[WRITE_END]);
		dup2(fd[WRITE_END], STDOUT_FILENO);
	//	printf("Esto no se tiene que ver\n");
	}
	if (i == num_commands)
	{
		//fprintf(stderr, "restoring%d\n", shell->fd_out);
		dup2(shell->fd_out, STDOUT_FILENO);
	//	printf("estoy hasta los huevos\n");
	//printf("----%d\t%d\n", fd[WRITE_END], fd[READ_END]);
		//close(fd[WRITE_END]);
		//close(fd[READ_END]);
	}
}
void hijo_de_puta(t_shell *shell, t_cmd_table *temp_cmd_table, char *path)
{
	if (isbuiltin(temp_cmd_table->command))
	{
		execute_builtin(temp_cmd_table , temp_cmd_table->command);
		exit(0);
	}
	//fprintf(stderr, "HOLAA\n");
	execve(path, temp_cmd_table->args, shell->ownenvp); //ejecutamos
	perror("esta mierda no funciona");
	exit(0);
}

void	redir_files(t_cmd_table *temp_cmd_table, int fd[2], int last_fd[2], int i, int num_commands)
{
	if(i == 0)
	{
		if(temp_cmd_table->outfile)
		{
			dup2(redirection(temp_cmd_table->outfile), STDOUT_FILENO);
			close(fd[WRITE_END]);
		}
		if(temp_cmd_table->infile)
			dup2(indirection(temp_cmd_table->infile), STDIN_FILENO);
	}
	if(i == num_commands)
	{
		if(temp_cmd_table->outfile)
			dup2(redirection(temp_cmd_table->outfile), STDOUT_FILENO);
		if(temp_cmd_table->infile)
			close(last_fd[READ_END]);
			dup2(indirection(temp_cmd_table->infile), STDIN_FILENO);
	}
	else
	{
		if(temp_cmd_table->outfile)
		{
			close(fd[WRITE_END]);
			dup2(redirection(temp_cmd_table->outfile), STDOUT_FILENO);
		}
		if(temp_cmd_table->infile)
		{
			close(last_fd[READ_END]);
			dup2(indirection(temp_cmd_table->infile), STDIN_FILENO);
		}
	}
	
		
}
void execute(t_shell *shell)
{

	int			num_commands;
	t_list		*temp_node;
	t_cmd_table *temp_cmd_table;

	shell->fd_in = dup(STDIN_FILENO);
	shell->fd_out = dup(STDOUT_FILENO);
	num_commands = ft_lstsize(shell->cmd_list);
	temp_node = shell->cmd_list;
	temp_cmd_table = NULL;
	if (num_commands == 1)
	{
		temp_cmd_table = (t_cmd_table *)shell->cmd_list->content;
		dup2(redirection(temp_cmd_table->outfile), STDOUT_FILENO);
		dup2(indirection(temp_cmd_table->infile), STDIN_FILENO);
		if(!temp_cmd_table->command)
			return ;
		if(temp_cmd_table->command && isbuiltin(temp_cmd_table->command))
			execute_builtin(temp_cmd_table, temp_cmd_table->command);
		else
			execute_single_bin(shell, temp_cmd_table);
		dup2(shell->fd_out, STDOUT_FILENO);
		dup2(shell->fd_in, STDIN_FILENO);
		close(shell->fd_out);
		close(shell->fd_in);
	}
	else
	{
		int		i;
		int		pid;
		char	*path;
		int		status;
		int		fd[2];
		int		last_fd[2];

		i = 0;
		num_commands--;
		while (temp_node)
		{
			//fprintf(stderr, "holo\n");
			temp_cmd_table = (t_cmd_table*)temp_node->content;
			if (is_absolute_path(temp_cmd_table->command))	//coge el path del binario, si usa un binario, en builting da igual.
				path = temp_cmd_table->command;
			else
				path = pathing(temp_cmd_table->command, shell->ownenvp);
			pipe(fd);
			redirfds(i, num_commands, fd, last_fd, shell);
			redir_files(temp_cmd_table, fd, last_fd, i, num_commands);
			pid = fork();
			if (pid == 0)
				hijo_de_puta(shell, temp_cmd_table, path);
			//fprintf(stderr, "fork out\n");
			last_fd[READ_END] = fd[READ_END];
			last_fd[WRITE_END] = fd[WRITE_END];

			fd[READ_END] = 0;
			fd[WRITE_END] = 1;

			temp_node = temp_node->next;
			i++;
		}
		i = 0;
		while (i < num_commands + 1)
		{
			waitpid(-1, &status, 0);
			i++;
		}
		dup2(shell->fd_out, STDOUT_FILENO);
		dup2(shell->fd_in, STDIN_FILENO);
		close(shell->fd_out);
		close(shell->fd_in);
	}	
}
