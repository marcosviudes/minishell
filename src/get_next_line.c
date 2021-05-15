/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 19:08:31 by mviudes           #+#    #+#             */
/*   Updated: 2021/05/15 11:38:25 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line.h>
#include <libft.h>

int	print_line(char **file, char **line, int i)
{
	char	*temp;
	int		x;

	if (i == 0 && !file)
	{
		*line = ft_strdup("");
		return (0);
	}
	x = 0;
	temp = 0;
	while ((*file)[x] != '\n' && (*file)[x])
		x++;
	*line = ft_substr(*file, 0, x);
	if ((*file)[x] == '\n')
		temp = ft_strdup(ft_strchr(*file, '\n') + 1);
	free(*file);
	*file = temp;
	if (!temp)
		return (0);
	else
		return (1);
}

int	get_next_line(int fd, char **line)
{
	int			i;
	static char	*file[4096];
	char		*temp;
	char		buf[1 + 1];

	i = 1;
	while (i > 0)
	{
		i = read(fd, buf, 1);
		if (i < 0)
			return (-1);
		buf[i] = '\0';
		if (file[fd] == NULL)
			file[fd] = ft_strdup("");
		temp = ft_strjoin(file[fd], buf);
		free(file[fd]);
		file[fd] = temp;
		if (ft_strchr(file[fd], '\n'))
			break ;
	}
	return (print_line(&file[fd], line, i));
}
