#include <minishell.h>
#include <readline/readline.h>

void	signal_init(void)
{
	signal(SIGQUIT, signal_handler_sigquit);
	signal(SIGINT, signal_handler_sigint);
}

void	signal_handler_sigquit(int signum)
{
	(void)signum;
	if (g_shell->pid > 0)
	{
		write(1, "\nQuit:\r\n", 8);
		kill(g_shell->pid, SIGQUIT);
		rl_point = 0;
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	else
	{
		write(1, "\33[2K", 4);
		write(1, "terminator$ ", 12);
		write(1, rl_line_buffer, rl_end);
		rl_redisplay();
	}
}

void	signal_handler_sigint(int signum)
{	
	(void)signum;
	if (g_shell->mode == M_HEREDOC)
	{
		g_shell->heredoc_value = 1;
		rl_redisplay();
		write(1, "\n", 1);
	}
	else if (g_shell->pid != -1)
	{
		kill(g_shell->pid, SIGINT);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	else
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
