/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 15:27:35 by mviudes           #+#    #+#             */
/*   Updated: 2021/05/17 15:45:48 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BUILTIN_MAX	3

typedef struct s_shell
{
	int			example;
}				t_shell;

typedef struct s_builtin
{
	char	*name;
	int		(*func)(t_shell *shell, char **argv);
}			t_builtin;
​
int	builtin_cd(t_shell *shell, char **argv)
{
	return (0);
}
​
int	builtin_echo(t_shell *shell, char **argv)
{
	return (0);
}
​
int	builtin_exit(t_shell *shell, char **argv)
{
	return (1);
}
​
int	builtin_pwd(t_shell *shell, char **argv)
{
	return (0);
}
​
t_builtin *init_builtin(void)
{
	t_builtin	*builtin;
​
	builtin = malloc(sizeof(t_builtin) * BUILTIN_MAX);
	builtin[0].name = "cd";
	builtin[0].func = (*builtin_cd);
	builtin[1].name = "echo";
	builtin[1].func = (*builtin_echo);
	builtin[2].name = "exit";
	builtin[2].func = (*builtin_exit);
	builtin[3].name = "pwd";
	builtin[3].func = (*builtin_pwd);
​
​
}
​
int main(void)
{
	int		i;
	char	*line;
	char	**argv;
​
	while (get_next_line(0, &line))
	{
		argv = ft_split(line, ' ');
		i = 0;
		while (i < BUILTIN_MAX)
		{
			if (ft_strcmp(builtin[i].name, argv[0]) == 0)
			{
				if (builtin[i].func(shell, argv))
					break ;
			}
		}
		free(argv);
		free(line);
	}
	free(argv);
	free(line);
}