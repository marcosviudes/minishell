#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>			//necesarioi para fork;
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>			//necesario para wait();
# include <sys/ioctl.h>
# include <sys/types.h>
# include <dirent.h>
# include <signal.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

# include <libft.h>
# include <get_next_line.h>
# include <dllst.h>

# define BUFSIZE		8
# define BUFFER_SIZE	8
# define TERM_NAME		"terminator$ "

typedef struct s_shell
{
	char			*prompt;
	char			*buff;
	char			*line;
	int				prompt_len;

}				t_shell;


//void		prompt_config(t_shell *shell, char *prompt_str);
#endif
