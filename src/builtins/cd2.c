#include <minishell.h>

int	only_cd(t_shell *shell)
{
	char	**aux;

	aux = ft_getenvptr("OLDPWD=", shell);
	free(*aux);
	*aux = ft_strjoin("OLDPWD=", ft_getenvcontent("PWD=", shell));
	aux = ft_getenvptr("PWD=", shell);
	free(*aux);
	*aux = ft_strjoin("PWD=", ft_getenvcontent("HOME=", shell));
	chdir(ft_getenvcontent("HOME=", shell));
	//ft_free_matrix(aux); 
	return (0);
}
