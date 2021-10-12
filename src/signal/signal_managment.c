#include <minishell.h>
# include <readline/readline.h>

void signal_init(void)
{
	signal(SIGQUIT, signal_handler_sigquit);
	signal(SIGKILL, signal_handler_sigkill);
	signal(SIGINT, signal_handler_sigint);
}

void signal_handler_sigquit(int signum)
{
	(void)signum;
	printf("sigquit pressed");
	if(g_shell->pid == 0)
		exit(0);
}

void signal_handler_sigkill(int signum)
{
	(void)signum;
	printf("sigkill pressed");

		exit(0);
}

void signal_handler_sigint(int signum)
{	
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
