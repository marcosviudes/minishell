/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnavarro <cnavarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 22:15:24 by mviudes           #+#    #+#             */
/*   Updated: 2021/10/17 17:08:07 by cnavarro         ###   ########.fr       */
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