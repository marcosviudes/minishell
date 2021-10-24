#include <minishell.h>
# include <readline/readline.h>

void signal_init(void)
{

	signal(SIGQUIT, SIG_IGN);
	//signal(SIGINT, SIG_IGN);
//	signal(SIGTERM, SIG_IGN);

	//if(g_shell->pid != -1)
			signal(SIGQUIT, signal_handler_sigquit);
	signal(SIGINT, signal_handler_sigint);
}

void signal_handler_sigquit(int signum)  //backslash
{
	(void)signum;
	
	if(g_shell->pid > 0){
		write(1, "\nQuit:\r\n", 8);
		kill(g_shell->pid, SIGQUIT);
		//signal(SIGQUIT, SIG_DFL);
		rl_point = 0;
		rl_replace_line("", 0);
		rl_on_new_line();
		//rl_redisplay();
	}
	else
	{
		rl_redisplay();;
	}
	/*
	{
		kill(0, SIGTERM);
		printf("\nesto hace un sigquit dentro de un proceso, PID: %i\n", g_shell->pid);
		rl_replace_line("", 0);
		rl_on_new_line();
	}*/
	/*else {
		printf("\nesto hace un sigquit en el padre\n");
	}*/
	//write(1, "\nQuit\n", 6);
//	exit(0);
}

void signal_handler_sigint(int signum)
{	

	(void)signum;

	if(g_shell->mode == M_HEREDOC)
	{
		g_shell->heredoc_value = 1;
		rl_redisplay();
		write(1, "\n", 1);
	}
	else if(g_shell->pid != -1)
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