/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 01:23:57 by mviudes           #+#    #+#             */
/*   Updated: 2021/10/27 01:23:58 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	child_process(t_shell *shell, t_cmd_table *temp_cmd_table, char *path)
{
	int	ret;

	signal(SIGQUIT, SIG_DFL);
	if (temp_cmd_table->command && isbuiltin(temp_cmd_table->command))
	{
		execute_builtin(temp_cmd_table, temp_cmd_table->command, shell);
		exit(0);
	}
	if (shell->execute == 1)
		ret = execve(path, temp_cmd_table->args, shell->ownenvp);
	printf("bash: %s: command not found\n", temp_cmd_table->command);
	exit(127);
}

void	execute_commands_single(t_shell *shell)
{
	t_cmd_table	*temp_cmd_table;
	int			outfile;
	int			infile;

	temp_cmd_table = (t_cmd_table *)shell->cmd_list->content;
	outfile = redirection(temp_cmd_table->outfile);
	infile = indirection(temp_cmd_table->infile);
	if (outfile == -1 || infile == -1)
	{
		perror("terminator");
		shell->execute = 0;
		return ;
	}
	if (!temp_cmd_table->command)
	{
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

void	set_first_last(t_shell *shell)
{
	int			flag;
	t_list		*cmd_list;
	t_cmd_table	*temp_cmd_table;

	flag = 0;
	cmd_list = shell->cmd_list;
	while (cmd_list != NULL)
	{
		temp_cmd_table = (t_cmd_table *)cmd_list->content;
		temp_cmd_table->num_command = IS_NODE_MIDLE;
		if (flag == 0)
			temp_cmd_table->num_command = IS_NODE_FIRST;
		flag = 1;
		if (!cmd_list->next && temp_cmd_table)
			temp_cmd_table->num_command = IS_NODE_LAST;
		cmd_list = cmd_list->next;
	}
}

void	execute_commands_multiple(t_shell *shell, int num_commands)
{
	char		*path;
	int			fd[2];
	int			last_fd[2];
	t_cmd_table	*temp_cmd_table;
	t_list		*temp_node;

	temp_node = shell->cmd_list;
	num_commands--;
	set_first_last(shell);
	while (temp_node)
	{
		temp_cmd_table = (t_cmd_table *)temp_node->content;
		path = get_final_path(shell, temp_cmd_table);
		pipe(fd);
		redirfds(temp_cmd_table, fd, last_fd, shell);
		redir_files(shell, temp_cmd_table, fd, last_fd);
		shell->pid = fork();
		if (shell->pid == 0)
			child_process(shell, temp_cmd_table, path);
		fd_copy_restore(fd, last_fd);
		temp_node = temp_node->next;
		free(path);
	}
	wait_for_childs(shell, num_commands);
	fd_close(fd, last_fd);
}

void	execute(t_shell *shell)
{
	int				num_commands;
	t_cmd_table		*temp_cmd_table;
	struct termios	old;

	tcgetattr(0, &old);
	shell->mode = M_EXECUTE;
	shell->fd_in = dup(STDIN_FILENO);
	shell->fd_out = dup(STDOUT_FILENO);
	num_commands = ft_lstsize(shell->cmd_list);
	temp_cmd_table = NULL;
	shell->execute = 1;
	if (num_commands == 1)
		execute_commands_single(shell);
	else
		execute_commands_multiple(shell, num_commands);
	fd_default_restore(shell);
	if (shell->flag_heredoc_file)
		unlink(".tempheredoc");
	shell->flag_heredoc_file = 0;
	tcsetattr(0, TCSANOW, &old);
}
