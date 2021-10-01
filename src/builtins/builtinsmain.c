#include <minishell.h>

int	main(int argc, char **argv, char **envp)
{
	ft_echo(int argc, char **argv);
	ft_cd(int argc, char **argv, char **envp);
	ft_pwd(char **envp);
	ft_export(int argc, char **argv, char **envp);
	ft_unset(int argc, char **argv, char **envp);
	ft_env(int argc, char **argv, char **envp);
	ft_exit(int argc, char **argv, char **envp);
}
