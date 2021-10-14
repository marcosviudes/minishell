#include <minishell.h>

char	*ft_getenvcontent(char *header)
{
	int		i;
	char	*ret;

	i = 0;
	while (g_shell->ownenvp[i])
	{
		if (ft_strncmp(g_shell->ownenvp[i], header, ft_strlen(header)) == 0)
		{
			ret = ft_substr(g_shell->ownenvp[i], ft_strlen(header),
					ft_strlen(g_shell->ownenvp[i]) - ft_strlen(header));
			return (ret);
		}
		i++;
	}
	return (NULL);
}

char	**ft_getenvptr(char *header)
{
	int		i;
	char	**ret;

	i = 0;
	while (g_shell->ownenvp[i])
	{
		if (ft_strncmp(g_shell->ownenvp[i], header, ft_strlen(header)) == 0)
		{
			ret = &g_shell->ownenvp[i];
			return (ret);
		}
		i++;
	}
	return (NULL);
}

char	*ft_getenvcpy(char *header)
{
	int		i;
	char	*ret;

	i = 0;
	while (g_shell->ownenvp[i])
	{
		if (ft_strncmp(g_shell->ownenvp[i], header, ft_strlen(header)) == 0)
		{
			ret = ft_strdup(g_shell->ownenvp[i]);
			return (ret);
		}
		i++;
	}
	return (NULL);
}