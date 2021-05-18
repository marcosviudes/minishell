#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>		//necesarioi para fork;
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>		//necesario para wait();
# include <sys/ioctl.h>
# include <sys/types.h>
# include <dirent.h>
# include <signal.h>
# include <errno.h>
# include <term.h>
# include <termios.h>
# include <curses.h>

# include <libft.h>
# include <get_next_line.h>
# include <dllst.h>

# define BUFSIZE		8
# define BUFFER_SIZE	8
# define HISTORY_PATH	"./minishell_history.txt"

typedef struct s_shell
{
	struct termios	native;
	struct termios	my_term;
	char			*prompt;
	char			*buff;
	char			*line;
	int				prompt_len;
	int				read_bytes;
	t_dllist		*history;
}				t_shell;

void	prompt_config(t_shell *shell, char *prompt_str);
void	prompt_put(t_shell *shell);

t_dllist	*history_import(char* string, int max_len);
void		history_print_all(t_dllist *history);
void		read_stdin(t_shell *shell);

int	set_terminal_mode(t_shell *shell);
# define TERM_NAME "terminator$ "
#endif
