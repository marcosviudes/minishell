/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 22:15:24 by mviudes           #+#    #+#             */
/*   Updated: 2021/05/12 22:17:32 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>	//necesario para wait();
#include <unistd.h>		//necesarioi para fork;

int		main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;

	fork();	//fork crea un proceso hijo;
			//devuelve el pid del proceso hijo
			//y si falla, -1
	printf("Hello World\n");
	return (0);
}