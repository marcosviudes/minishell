/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 01:24:02 by mviudes           #+#    #+#             */
/*   Updated: 2021/10/27 01:24:02 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_absolute_path(char *command)
{
	if (command != NULL)
		if (*command == '/' || *command == '.')
			if (access(command, X_OK | F_OK) == 0)
				return (1);
	return (0);
}

static char	**del_and_join(char **table, char *joined, int i)
{
	char	**aux;
	int		this_i;

	aux = malloc(sizeof(char *) * (count_lines(table) + 1));
	this_i = 0;
	while (this_i < i)
	{
		aux[this_i] = ft_strdup(table[this_i]);
		this_i++;
	}
	aux[this_i] = ft_strjoin(table[this_i], joined);
	this_i++;
	while (table[this_i])
	{
		aux[this_i] = ft_strdup(table[this_i]);
		this_i++;
	}
	aux[this_i] = NULL;
	ft_free_matrix(table);
	return (aux);
}

int	search_for_line(char **envp)
{
	int		i;
	char	*cosa;

	i = 0;
	while (envp[i])
	{
		cosa = ft_strnstr(envp[i], "PATH=", 5);
		if (cosa != NULL)
			return (i);
		i++;
	}
	return (-1);
}

char	*the_path(int fd, char **paths, int i)
{
	char	*the_path;

	the_path = NULL;
	the_path = ft_strdup(paths[i]);
	ft_free_matrix(paths);
	close(fd);
	return (the_path);
}

char	*pathing(char *command, char **envp)
{
	char	**paths;
	int		i;
	int		fd;

	if (command == NULL)
		return (NULL);
	if (search_for_line(envp) == -1)
		return (NULL);
	paths = ft_split(&envp[search_for_line(envp)][5], ':');
	i = 0;
	while (paths[i])
	{
		paths = del_and_join(paths, "/", i);
		paths = del_and_join(paths, command, i);
		fd = open(paths[i], O_RDONLY);
		if (fd >= 0)
			return (the_path(fd, paths, i));
		i++;
	}
	ft_free_matrix(paths);
	return (NULL);
}
