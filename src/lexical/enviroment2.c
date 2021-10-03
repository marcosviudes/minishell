#include <minishell.h>

char	*get_before_dolar(char *string)
{
	int		i;
	int		count;
	char	*ret;

	i = 0;
	count = 0;
	while(string[i] != '$')
		i++;
	ret = malloc(sizeof(char) * (i + 1));
	while (count < i)
	{
		ret[count] = string[count];
		count++;
	}
	ret[count] = '\0';
	return (ret);
}
char	*get_after_dolar(char *pdolar)
{
	int i;
	int j;
	char *ret;


	j = 0;
	i = 1;
	while (ft_isalnum(pdolar[i]))
		i++;
	while (pdolar[j + i])
		j++;
	ret = ft_calloc(sizeof(char), j);
	ret[0] = '\0';
	j = 0;
	while (pdolar[i + j])
	{
		ret[j] = pdolar[i + j];
		j++;
	}
	return (ret);
}
/*
char *exception(char *string, char *pdolar, char **envp)
{
	char *finalstring;
	char *aux;

	aux = ft_strtrim(string, "'");
	free(string);
	finalstring = ft_strjoin("'", ft_strjoin(ft_finalstring(aux, pdolar, envp), "'"));
	return (finalstring);
}
*/