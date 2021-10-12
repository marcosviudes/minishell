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
	if(ft_strncmp(string, "echo", ft_strlen("export")) == 0)
		return(1);
	if(ft_strncmp(string, "cd", ft_strlen("cd")) == 0)
		return(1);
	if(ft_strncmp(string, "pwd", ft_strlen("pwd")) == 0)
		return(1);
	if(ft_strncmp(string, "export", ft_strlen("export")) == 0)
		return(1);
	if(ft_strncmp(string, "unset", ft_strlen("unset")) == 0)
		return(1);
	if(ft_strncmp(string, "env", ft_strlen("env")) == 0)
		return(1);
	if(ft_strncmp(string, "exit", ft_strlen("exit")) == 0)
		return(1);
	return(0);
}
/*
void builtin(t_shell *shell)
{
	int		fd_in;
	int		fd_out;

	fd_in = dup(0);
	fd_out = dup(1);

	printf("esto ejecuta un builtin\nj");
}
*/
void	execute_builtin(t_shell *shell, char *command)
{
	t_cmd_table *temp;

	printf("esto ejecuta un builtin\n");
	temp = shell->cmd_list->content;
	if(ft_strncmp(command, "echo", ft_strlen("echo")) == 0)
		ft_echo(&temp->args[1]);
	if(ft_strncmp(command, "cd", ft_strlen("cd")) == 0)
		ft_cd(&temp->args[1]);
	if(ft_strncmp(command, "pwd", ft_strlen("pwd")) == 0)
		ft_pwd();
	if(ft_strncmp(command, "export", ft_strlen("export")) == 0)
		ft_export(&temp->args[1]);
//	if(ft_strncmp(command, "unset", ft_strlen("unset")) == 0)
//		ft_unset();
	if(ft_strncmp(command, "env", ft_strlen("env")) == 0)
		ft_env();
//	if(ft_strncmp(command, "exit", ft_strlen("exit")) == 0)
//		ft_exit();
}


int	open_file(char *file_name, int mode)
{
	if(access(file_name, F_OK ) == 0 && access(file_name, R_OK | W_OK) != 0)
		return(-1);
	if(mode == APPEND_ON)
		return(open(file_name, O_APPEND | O_RDWR | O_CREAT, 00644));
	else
		return(open(file_name, O_WRONLY | O_CREAT, 00644));
	
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



int	command_redirection(t_list *redir, int finfout)
{
	//t_list *redir;
	t_table_redir redir_table;
	int		fd;
	int		i;

	i = 0;
	//redir = table->outfile;
	if(redir)
	{
		while(redir)
		{
			redir_table = *(t_table_redir*)redir->content;
			if(i > 0)
				close(fd);
			fd = open_file(redir_table.file, redir_table.append);
			if(fd == -1)
				return(1);
			i++;
			redir = redir->next;
		}
		return(fd);
	}
	return(finfout);
}

void execute_single_bin(t_shell *shell, t_cmd_table *table)
{
	char	*path;
	pid_t 	pid;

	path = NULL;
	printf("--------%s\n", table->command);
	if(is_absolute_path(table->command))
		path = table->command;
	else
		path = pathing(table->command, shell->ownenvp);
	printf("%s\n", path);
	if(!path)
		return;
	pid = fork();
	if(pid == 0){
//		shell->fd_in = dup(STDIN_FILENO);
//		shell->fd_out = dup(STDOUT_FILENO);
	//	dup2(command_redirection(table->outfile, STDOUT_FILENO), STDOUT_FILENO);
	//	dup2(command_redirection(table->infile, STDIN_FILENO), STDIN_FILENO);
		execve(path, table->args, shell->ownenvp);
	}
	shell->pid = pid;
	wait(&shell->pid);
	return;
}


void execute(t_shell *shell)
{
	int			(*fd)[2];
	int			num_commands;
	t_list		*temp_node;
	t_cmd_table *temp_cmd_table;

//	(void)fd;

	num_commands = ft_lstsize(shell->cmd_list);
	fd = malloc(sizeof(int*) * num_commands - 1);
	temp_node = shell->cmd_list;
	temp_cmd_table = NULL;
	if(num_commands == 1)
	{
		temp_cmd_table = (t_cmd_table*)shell->cmd_list->content;
		//close(STDIN_FILENO);
		//close(STDOUT_FILENO);
	//	dup2(command_redirection(temp_cmd_table->outfile, STDOUT_FILENO), STDOUT_FILENO);
	//	dup2(command_redirection(temp_cmd_table->infile, STDIN_FILENO), STDIN_FILENO);
		if(temp_cmd_table->command && isbuiltin(temp_cmd_table->command))
			execute_builtin(shell, temp_cmd_table->command);
		else
			execute_single_bin(shell, temp_cmd_table);
		//dup2(shell->fd_out, STDOUT_FILENO);
		//dup2(shell->fd_in, STDIN_FILENO);
		//close(shell->fd_out);
		//close(shell->fd_in);
	}
	else
	{
		int	i;

		i = 0;
		while (i < num_commands - 1)
		{
			pipe(fd[i]);
			i++;
		}
	}
//	dup2(shell->fd_out, STDOUT_FILENO);
//	dup2(shell->fd_in, STDIN_FILENO);
//	close(shell->fd_out);
//	close(shell->fd_in);
//	shell->fd_in = dup(STDIN_FILENO);
//	shell->fd_out = dup(STDOUT_FILENO);
}