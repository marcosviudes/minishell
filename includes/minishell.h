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

# define GREAT			1
# define LESS			2
# define GREAT_GREAT	3
# define LESS_LESS		4
# define PIPE			5

typedef struct s_info t_info;
typedef struct	s_info
{
	char			*string;
	char			type;
	int				marks;
	struct	s_info	*next;
	t_info			*prev;
}				t_info;

typedef struct	s_shell
{
	char			*prompt;
	char			*buff;
	char			*line;
	int				prompt_len;
	char			**line_splitted;
	t_list			*cmd_list;
	t_info			*info;
}				t_shell;


typedef struct s_cmd_table
{
	char		*command;
	char		**args;
	char		*outfile;
	char		*infile;
}				t_cmd_table;


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

//parse
void	parse(t_shell *shell);
char	**ft_insert_string2(char **table, char *str);
void	print_command(void *cmd);
void	info_free(t_info *info);
void	info_add_prev(t_info *info);
void	print_list(t_info *info);
void	free_table(void *arg);
//void		prompt_config(t_shell *shell, char *prompt_str);

//signal
void signal_init(void);
void signal_handler_sigquit(int signum);
void signal_handler_sigkill(int signum);
void signal_handler_sigint(int signum);

#endif
