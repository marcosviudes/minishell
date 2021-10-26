/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_open_files.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 01:24:15 by mviudes           #+#    #+#             */
/*   Updated: 2021/10/27 01:24:16 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	open_file(char *file_name, int mode)
{
	if (access(file_name, F_OK) == 0 && access(file_name, R_OK | W_OK) != 0)
		return (-1);
	if (mode == APPEND_ON)
		return (open(file_name, O_APPEND | O_WRONLY | O_CREAT, 00644));
	else
		return (open(file_name, O_TRUNC | O_WRONLY | O_CREAT, 00644));
}

int	redirection(t_list *redir)
{
	t_table_redir	redir_table;
	int				fd;
	int				i;

	i = 0;
	if (redir)
	{
		while (redir)
		{
			redir_table = *(t_table_redir *)redir->content;
			if (i > 0)
				close(fd);
			fd = open_file(redir_table.file, redir_table.append);
			if (fd == -1)
				return (-1);
			i++;
			redir = redir->next;
		}
		return (fd);
	}
	return (STDOUT_FILENO);
}

int	indirection(t_list *redir)
{
	t_table_redir	redir_table;
	int				fd;
	int				i;

	i = 0;
	if (redir)
	{
		while (redir)
		{
			redir_table = *(t_table_redir *)redir->content;
			if (i > 0)
				close(fd);
			if (access(redir_table.file, F_OK) == 0
				&& access(redir_table.file, R_OK | W_OK) != 0)
				return (-1);
			fd = open(redir_table.file, O_RDWR, 00644);
			if (fd == -1)
				return (-1);
			i++;
			redir = redir->next;
		}
		return (fd);
	}
	return (STDIN_FILENO);
}
