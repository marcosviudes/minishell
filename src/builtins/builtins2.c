#include <minishell.h>

int	ft_env(void)
{
	int i;

	i = 0;
	while (g_shell->ownenvp[i])
	{
		printf("%s\n", g_shell->ownenvp[i]);
		i++;
	}
	return (0);
}
/*
int	ft_unset(int argc, char **argv, char **envp)
{
	return (0);
}

int	ft_exit(void)
{
	//free(cosas);
	printf("exit\n");
	exit(0);
	return (0);
}
*/