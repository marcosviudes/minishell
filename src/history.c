/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 14:53:42 by mviudes           #+#    #+#             */
/*   Updated: 2021/05/15 15:32:23 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dllst.h>
#include <minishell.h>

char	*history_get_buff(t_dllist *history)
{
	return(history->buff);
}

int	history_import(t_dllist **history)
{
	FILE	*fd;
	char	*buff;
	
	//	if(*history != NULL)
	//		ft_dllstclear(history, )
	fd = open(HISTORY_PATH, O_WRONLY | O_CREAT, S_IRWXU);
	//manejar error del fd;
	while(get_next_line(fd, &buff) > 0)
	{
		dllist_new(buff);
		dllstadd_front(history, dllist_new);
	}
	close(fd);
}

int	history_export(t_dllist **history)
{
	return (0);
}