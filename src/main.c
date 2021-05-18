/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnavarro <cnavarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 21:26:16 by mviudes           #+#    #+#             */
/*   Updated: 2021/05/18 17:16:44 by cnavarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_all(t_shell *shell)
{
	free(shell->prompt);
	free(shell);
}

/* The fucniton disabled the normal function of the terminal
 * with tcgetattr get the configuration of the native terminal
 *	ECHO	: disables the display of characters
 *	ICANON	: allow reading byte-by-byte
 *	ISIG	: disable ctrl-C signal; wich terminate the program
 *	OPOST	: 
 *	VMIN	:
 *	VTIMR	: disable timeout for read function
 */

int	set_terminal_mode(t_shell *shell)
{
	tcgetattr(STDIN_FILENO, &shell->native);
	shell->my_term = shell->native;
	shell->my_term.c_lflag &= ~(ECHO);
	shell->my_term.c_lflag &= ~(ICANON);
	shell->my_term.c_lflag &= ~(ISIG);
	shell->my_term.c_lflag &= ~(OPOST);
	shell->my_term.c_cc[VMIN] = 0;
	shell->my_term.c_cc[VTIME] = 1;
	tcsetattr(STDIN_FILENO,  TCSANOW, &shell->my_term);
	return(0);
}

/*
int	set_terminal_mode(t_shell *shell)
{
	struct termios my_term;
	
	tcgetattr(STDIN_FILENO, &shell->native);
	my_term = shell->native;
	my_term.c_lflag &= ~(ECHO);
	my_term.c_lflag &= ~(ICANON);
	my_term.c_lflag &= ~(ISIG);
	my_term.c_lflag &= ~(OPOST);
	my_term.c_cc[VMIN] = 0;
	my_term.c_cc[VTIME] = 1;
	tcsetattr(STDIN_FILENO,  TCSANOW, &my_term);
	return(0);
}*/


t_shell	*init_structure(t_shell *shell)
{
	shell = malloc(sizeof(t_shell));
	shell->tcps = init_tercaps(shell);
	return(shell);
}

void	read_in(t_shell *shell)
{
		shell->buff = ft_calloc(1, BUFSIZE + 1);
		while(ft_strncmp(shell->buff, "\n", 2) != 0)
		{
			shell->read_bytes = read(STDIN_FILENO, shell->buff, BUFSIZE);
			shell->buff[shell->read_bytes] = '\0';
			write(STDOUT_FILENO, shell->buff, shell->read_bytes);
			if (!ft_isprint(shell->buff[0]) && shell->buff[0] != '\0')
				tercaps(&shell->buff[0], shell);
			if(shell->buff[0] == 'q')
			{
				system("leaks minishell");
				system("reset"); // reset zsh terminal after run program, to reset termios
				exit(0);
			}
			if(shell->buff[0] == 'h')
			{
				ft_putchar_fd('\n', 1);
				history_print_all(shell->history);
			}
		}
		free(shell->buff);
}

int	main(int argc, char **argv)
{
	t_shell	*shell;
	
	(void)argc;
	(void)argv;
	shell = NULL;
	shell = init_structure(shell); 
	set_terminal_mode(shell);
	shell->history = history_import(argv[1], 20);
//	history_print_all(shell->history);
	prompt_config(shell, TERM_NAME);
	while (1)
	{
		prompt_put(shell);
		read_in(shell);
	}
	free_all(shell);
	system("leaks minishell");
	return (0);
}
