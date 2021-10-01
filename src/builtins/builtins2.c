#include <minishell.h>

int	ft_unset(int argc, char **argv, char **envp)
{
	return (0);
}

int	ft_env(int argc, char **argv, char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		printf("%s", envp[i]);
		i++;
	}
	write(1, "\n", 1);
	return (0);
}

int	ft_exit(int argc, char **argv, char **envp)
{
	//free(cosas);
	exit(0);
	return (0);
}
