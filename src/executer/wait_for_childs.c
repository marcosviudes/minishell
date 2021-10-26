#include <minishell.h>

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
