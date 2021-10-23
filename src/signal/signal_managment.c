#include <minishell.h>
# include <readline/readline.h>

void signal_init(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_DFL);
	//		signal(SIGKILL, signal_handler_sigkill);
	//	signal(SIGQUIT, signal_handler_sigquit);
	signal(SIGINT, signal_handler_sigint);
}

void signal_handler_sigquit(int signum)  //backslash
{
	(void)signum;

	write(1, "Quit:\n", 6);
	kill(g_shell->pid, SIGINT);
	rl_replace_line("", 0);
	rl_on_new_line();
//	printf("\n");
/*	if(g_shell->mode != M_READING){
		if (g_shell->pid == 0){
			printf("Quit\n");
			exit(0);
		}
	}*/

//	write(1, "\nQuit\n", 6);
//	exit(0);
}
/*
void signal_handler_sigkill(int signum)  // control-D
{
	(void)signum;
	printf("sigkill pressed");
	printf("exit\n");
	exit(0);
}*/

void signal_handler_sigint(int signum)
{	

	(void)signum;
	if(g_shell->pid != -1)
	{
		kill(g_shell->pid, SIGINT);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	else{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}