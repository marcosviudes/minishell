#include <minishell.h>

char	*get_final_path(t_shell *shell, t_cmd_table *table)
{
	char	*path;

	path = NULL;
	if (is_absolute_path(table->command))
		path = ft_strdup(table->command);
	else
		path = pathing(table->command, shell->ownenvp);
	return (path);
}

void	execute_single_bin(t_shell *shell, t_cmd_table *table)
{
	char			*path;
	int				ret;
	int				status;
	struct termios	old;

	ret = 0;
	path = NULL;
	path = get_final_path(shell, table);
	tcgetattr(0, &old);
	shell->pid = fork();
	if (shell->pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		ret = execve(path, table->args, shell->ownenvp);
		printf("bash: %s: command not found\n", table->command);
		exit(127);
	}
	free(path);
	wait(&status);
	tcsetattr(0, TCSANOW, &old);
	if (WIFEXITED(status))
		shell->return_value = WEXITSTATUS(status);
	return ;
}
