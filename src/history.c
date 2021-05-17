/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 14:53:42 by mviudes           #+#    #+#             */
/*   Updated: 2021/05/17 11:35:11 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dllst.h>
#include <minishell.h>

char	*history_get_buff(t_dllist *history)
{
	return(history->buff);
}

t_dllist	*history_import(char *file_path, int max_list_len)
{
	int			fd;
	char		*buff;
	t_dllist	*history;
	int			i;
	int			count;

	(void)count;
	(void)max_list_len;
	history = NULL;
//	count = 0;
	(void)file_path;
	fd = open("minishell_history.txt", O_RDONLY | O_CREAT, 0777);
	if(fd < 0){
		write(1, "no se pudo abrir el archivo", 27);
		exit(-1);
	}
	while((i = get_next_line(fd, &buff)) > 0)
	{
	//	if(count > max_list_len)				/delete last node if excedes to avoid overflow
	//	{
	//		count--;
	//		dllstddel_last(&history);
	//	}
//		if(buff[0] == '\0' )
//			continue;
		dllstadd_front(&history, dllist_new(buff));
	//	count++;
	}
	//free(buff);
	close(fd);
	return(history);
}

int	history_export(t_dllist **history)
{
	(void)history;
	return (0);
}

void	history_print_all(t_dllist *history)
{
	if(!history)
		return ;
	while(history->prev != NULL)
		history = history->prev;
	while(history != NULL)
	{
		ft_putendl_fd(history->buff, 1);
		history = history->next;
	}
}