#include "parse.h"

static int	split_indexing(char *str, int i)
{
	char	c;

	if (str[i] == '$' && str[i + 1] == '"')
		i++;
	c = str[i];
	if (str[i] == '"' || str[i] == '\'')
	{
		i++;
		while (str[i] != c && str[i] != '\0')
			i++;
	}
	else
	{
		i++;
		while (str[i] != '"' && str[i] != '\'' && str[i] != '\0' && str[i] != '$')
			i++;
		i--;
	}
	return (i);
}

static int	line_count(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		i = split_indexing(str, i);
		count++;
		i++; 
	}
	return (count);
}

char	**shell_split_quote(char *str)
{
	char		**res;
	const int	word = line_count(str);
	int			i;
	int			start;
	int			end;

	res = (char **)malloc(sizeof(char *) * (word + 1));
	i = 0;
	start = 0;
	while (i < word)
	{
		end = split_indexing(str, start);
		res[i] = ft_substr(str, start, end - start + 1);
		start = end + 1;
		i++;
	}
	res[word] = NULL;
	return (res);
}
