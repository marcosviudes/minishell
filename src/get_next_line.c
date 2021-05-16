/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 19:08:31 by mviudes           #+#    #+#             */
/*   Updated: 2021/05/16 22:02:37 by mviudes          ###   ########.fr       */
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
	char		buf[BUFFER_SIZE+ 1];

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
/*
char			*ft_strcdup(const char *src, int c)
{
	int			i;
	int			j;
	char		*s2;

	i = 0;
	j = 0;
	while (src[i] && src[i] != c)
		i++;
	s2 = malloc((i + 1) * sizeof(char));
	if (!(s2))
		return (0);
	while (j < i)
	{
		s2[j] = src[j];
		j++;
	}
	s2[j] = '\0';
	return (s2);
}

int				get_next_line(int fd, char **line)
{
	static char	*str[4096];
	char		buff[BUFFER_SIZE + 1];
	int			i;
	char		*tmp;

	!str[fd] ? str[fd] = ft_strcdup("", '\0') : str[fd];
	while ((i = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[i] = '\0';
		tmp = ft_strjoin(str[fd], buff);
		free(str[fd]);
		if (ft_strchr((str[fd] = tmp), '\n'))
			break ;
	}
	if (i < 0 || line == NULL)
		return (-1);
	*line = ft_strcdup(str[fd], '\n');
	tmp = NULL;
	if (str[fd][ft_strlen(*line)] != '\0')
		tmp = ft_strcdup(ft_strchr(str[fd], '\n') + 1, '\0');
	free(str[fd]);
	if ((str[fd] = tmp) == NULL)
		return (0);
	return (1);
}*/