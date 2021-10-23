#include <minishell.h>
# include <readline/readline.h>

void signal_handler_siguser(int signum)
{
	(void)signum;
	return;
}

void signal_init(void)
{
	signal(SIGQUIT, signal_handler_sigquit);
//	signal(SIGKILL, signal_handler_sigkill);
	signal(SIGINT, signal_handler_sigint);
}

void signal_handler_sigquit(int signum)  //backslash
{
	(void)signum;

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
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
