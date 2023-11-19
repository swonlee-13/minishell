#include "parse.h"

void	file_name_setter_value_set(char *token_string, int i, char c, int count)
{
	if (count == 1 && c == 'I')
		token_string[i] = 'F';
	else if (count == 1 && c == 'O')
		token_string[i] = 'E';
	else if (count == 2 && c == 'I')
		token_string[i] = 'H';
	else if (count == 2 && c == 'O')
		token_string[i] = 'G';
}

int	file_name_setter_sub(char *token_string, int i)
{
	const char	c = token_string[i];
	int			count;

	count = 0;
	while (token_string[i] == c)
	{
		count++;
		i++;
	}
	while (token_string[i] == ' ')
		i++;
	while (token_string[i] != ' ' && token_string[i] != '\0')
	{
		if (token_string[i] == 'A')
			file_name_setter_value_set(token_string, i, c, count);
		i++;
	}
	return (i);
}

void	file_name_setter(char *token_string)
{
	int	i;

	i = 0;
	while (token_string[i])
	{
		if (token_string[i] == 'I' || token_string[i] == 'O')
			i = file_name_setter_sub(token_string, i);
		else
			i++;
	}
}

int	dollar_sign_setter_quote(char *cmd, char *token_string, int i)
{
	const char	c = token_string[i];

	i++;
	if (c == 'S')
	{
		while (token_string[i] != 'S' && token_string[i] != '\0')
			i++;
		i++;
		return (i);
	}
	else if (c == 'D')
	{
		while (token_string[i] != 'D' && token_string[i] != '\0')
		{
			if (cmd[i] == '$' && token_string[i + 1] != 'D' && token_string[i + 1] != 'H')
				token_string[i] = '$';
			i++;
		}
	}
	return (i + 1);
}

void	dollar_sign_setter(char *cmd, char *token_string)
{
	int	i;

	i = 0;
	while (token_string[i])
	{
		if (token_string[i] == 'S' || token_string[i] == 'D')
			i = dollar_sign_setter_quote(cmd, token_string, i);
		else if (token_string[i] == 'A' && cmd[i] == '$')
		{
			token_string[i] = '$';
			i++;
		}
		else
			i++;
	}
}

void	token_setter(char *cmd, char *token_string)
{
	file_name_setter(token_string);
	dollar_sign_setter(cmd, token_string);
}
