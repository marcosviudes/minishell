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

# define APPEND_ON		1
# define APPEND_OFF		0

# define READ_END		0
# define WRITE_END		1

# define M_READING		0
# define M_HEREDOC		1
# define M_PARSE		2
# define M_EXECUTE		3

typedef struct s_info	t_info;

typedef struct s_info
{
	char			*string;
	char			type;
	int				marks;
	int				union_next;
	int				is_union;
	struct s_info	*next;
	t_info			*prev;
}				t_info;

typedef struct s_shell
{
	int				heredoc_value;
	int				flag_heredoc_file;
	int				mode;
	int				open_marks;
	char			**ownenvp;
	int				flag_command;
	int				flag_redirection;
	char			*line;
	int				prompt_len;
	char			**line_splitted;
	int				return_value;
	int				num_of_pipes;
	int				fd_out;
	int				fd_in;
	pid_t			pid;
	int				union_next;
	t_list			*cmd_list;
	t_info			*info;
}				t_shell;

t_shell					*g_shell;

typedef struct s_cmd_table
{
	char		*command;
	char		**args;
	t_list		*outfile;
	t_list		*infile;
}				t_cmd_table;

typedef struct s_table_redir
{
	char		*file;
	int			append;
}				t_table_redir;

typedef struct s_sort	t_sort;

typedef struct s_sort
{
	char		*line;
	t_sort		*next;
}				t_sort;

//lexer
void	lexical_analyzer(t_shell *shell);
int		quotation_marks(t_shell *shell, int i);
void	add_node(t_shell *shell, int i, char car);
void	env_transform(t_shell *shell);
char	*ft_finalstring(char *string, char *pdolar, char **envp);
void	arg_unions(t_shell *shell);
char	*get_dolar_string(char *pdolar, int *count, t_shell *shell);

//HIST_ENTRY **history;

//parse
void	parse(t_shell *shell);
void	parse_command(t_shell *shell, t_info *temp, t_cmd_table *table);
void	parse_redirection(t_shell *shell, t_table_redir *temp_redir,
			t_info *temp, t_cmd_table *table);
void	parse_indirection(t_shell *shell, t_table_redir *temp_redir,
			t_info *temp, t_cmd_table *table);
void	parse_heredoc(t_shell *shell, t_table_redir *temp_redir,
			t_info *temp, t_cmd_table *table);
void	parse_symbols(t_shell *shell, t_cmd_table **table, t_info *temp);
void	parse_words(t_shell *shell, t_table_redir *temp_redir,
			t_info *temp, t_cmd_table *table);
void	print_command(void *cmd);
void	info_free(t_info *info);
void	print_command(void *cmd);
void	info_add_prev(t_info *info);
void	print_list(t_info *info);
void	print_redir(void *redir);
void	free_table(void *arg);
int	ft_heredoc(t_shell *shell, t_info *temp);
//void		prompt_config(t_shell *shell, char *prompt_str);

//signal
void	signal_init(void);
void	signal_handler_sigquit(int signum);
void	signal_handler_sigkill(int signum);
void	signal_handler_sigint(int signum);

//executer
void	execute(t_shell *shell);

//builtings
int		ft_export(char **argv, t_shell *shell);
int		ft_env(t_shell *shell);
int		ft_pwd(t_shell *shell);
int		ft_echo(char **argv);
int		ft_cd(char **argv, t_shell *shell);
int		only_cd(t_shell *shell);
int		ft_unset(char **argv, t_shell *shell);
void	ft_exit(char **argv, int father);
void	sort_list(t_sort *list);
void	print_order_list(t_sort *list);
void	free_list(t_sort *list);
void	add_line_to_list(char *line, t_sort **ordered_list);

//utils
int		count_lines(char **table);
char	**ft_insert_string(char **table, char *str);
char	**ft_insert_string2(char **table, char *str);
void	ft_free_matrix(char **matrix);
char	*ft_getenvcontent(char *header, t_shell *shell);
char	**ft_getenvptr(char *header, t_shell *shell);
char	*ft_getenvcpy(char *header, t_shell *shell);
int		its_not_special(char digit);
char	**fill_env(char **envp);

//FREEE
void	free_table(void *arg);
#endif
