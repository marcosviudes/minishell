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

int	its_not_special(char digit)
{
	if (digit == ' ' || digit == '<'
		|| digit == '>' || digit == '|'
		|| digit == 34 || digit == 39)
		return (0);
	return (1);
}

char	**fill_env(char **envp)
{
	char	**new_envp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 1));
	while (j < i)
	{
		new_envp[j] = ft_strdup(envp[j]);
		j++;
	}
	new_envp[j] = NULL;
	return (new_envp);
}
