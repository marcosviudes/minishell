/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 21:26:16 by mviudes           #+#    #+#             */
/*   Updated: 2021/05/14 12:52:18 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_all(t_shell *shell)
{
	free(shell->prompt);
	free(shell);
}

int	set_terminal_mode(t_shell *shell)
{
	tcgetattr(STDIN_FILENO, &shell->native);
	shell->my_term = shell->native;
	shell->my_term.c_lflag &= ~(ECHO);
	tcsetattr(STDIN_FILENO,  TCSANOW, &shell->my_term);
	return(0);
}

t_shell	*init_structure(t_shell *shell)
{
	shell = ft_calloc(1, sizeof(t_shell));
	return(shell);
}
int	main(int argc, char **argv)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	shell = NULL;
	shell = init_structure(shell);
	set_terminal_mode(shell);
	prompt_config(shell, TERM_NAME);
	while (1)
	{
		prompt_put(shell);
		shell->buff = ft_calloc(1, BUFSIZE + 1);
		while(ft_strncmp(shell->buff, "\n", 2) != 0)
		{
			shell->read_bytes = read(STDIN_FILENO, shell->buff, BUFSIZE);
			shell->buff[shell->read_bytes] = '\0';
			printf("%s\n", shell->buff);
		}
		free(shell->buff);
	}
	free_all(shell);
	return (0);
}

