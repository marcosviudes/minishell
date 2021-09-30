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

typedef struct	s_info
{
	char			*string;
	char			type;
	int				marks;
	struct	s_info	*next;
}				t_info;

typedef struct	s_shell
{
	char			*prompt;
	char			*buff;
	char			*line;
	int				prompt_len;
	char			**line_splitted;
	t_info			*info;
}				t_shell;

/*
type:
	-w: word
	-s: simbolo
	-t: token 
marks:
	-0: normal
	-1: comillas dobles
	-2: comillas simples
*/

void	lexical_analyzer(t_shell *shell);
char	**ft_insert_string(char **table, char *str);
void	ft_free_matrix(char **matrix);
int		quotation_marks(t_shell *shell, int i);
void	ft_strerror(char *str, int num);
void	add_node(t_shell *shell, int i, char car);
void	env_transform(t_shell *shell, char **envp);
char	*get_before_dolar(char *string);
char	*get_after_dolar(char *pdolar);
char	*exception(char *string, char *pdolar, char **envp);
char	*ft_finalstring(char *string, char *pdolar, char **envp);

//HIST_ENTRY **history;

//void		prompt_config(t_shell *shell, char *prompt_str);
#endif
