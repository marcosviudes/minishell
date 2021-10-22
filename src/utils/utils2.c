#include <minishell.h>

char	*ft_getenvcontent(char *header, t_shell *shell)
{
	int		i;
	char	*ret;

	i = 0;
	while (shell->ownenvp[i])
	{
		if (ft_strncmp(shell->ownenvp[i], header, ft_strlen(header)) == 0)
		{
			ret = ft_substr(shell->ownenvp[i], ft_strlen(header),
					ft_strlen(shell->ownenvp[i]) - ft_strlen(header));
			return (ret);
		}
		i++;
	}
	return (NULL);
}

char	**ft_getenvptr(char *header, t_shell *shell)
{
	int		i;
	char	**ret;

	i = 0;
	while (shell->ownenvp[i])
	{
		if (ft_strncmp(shell->ownenvp[i], header, ft_strlen(header)) == 0)
		{
			ret = &shell->ownenvp[i];
			return (ret);
		}
		i++;
	}
	return (NULL);
}

char	*ft_getenvcpy(char *header, t_shell *shell)
{
	int		i;
	char	*ret;

	i = 0;
	while (shell->ownenvp[i])
	{
		if (ft_strncmp(shell->ownenvp[i], header, ft_strlen(header)) == 0)
		{
			ret = ft_strdup(shell->ownenvp[i]);
			return (ret);
		}
		i++;
	}
	return (NULL);
}