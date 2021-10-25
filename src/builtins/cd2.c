#include <minishell.h>

int	only_cd(t_shell *shell)
{
	char	**aux;
	char	*content;

	aux = ft_getenvptr("OLDPWD=", shell);
	free(*aux);
	content = ft_getenvcontent("PWD=", shell);
	*aux = ft_strjoin("OLDPWD=", content);
	free(content);
	aux = ft_getenvptr("PWD=", shell);
	free(*aux);
	content = ft_getenvcontent("HOME=", shell);
	*aux = ft_strjoin("PWD=", content);
	chdir(content);
	free(content);
	return (0);
}
