/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 19:22:13 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/01 19:22:16 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

int	redirection_tokenizer(char *cmd, int i, char *token_string, char c)
{
	while (cmd[i] == c)
	{
		if (c == '<')
			token_string[i] = 'I';
		else
			token_string[i] = 'O';
		i++;
	}
	return (i);
}

int	pipe_tokenizer(int i, char *token_string)
{
	token_string[i] = 'P';
	return (i + 1);
}

int	space_tokenizer(int i, char *cmd, char *token_string)
{
	if (cmd[i] == ' ')
		token_string[i] = ' ';
	else
		token_string[i] = '0';
	return (i + 1);
}

int	quote_tokenizer(char *cmd, int i, char *token_string, char c)
{
	if (cmd[i] == '\'')
		token_string[i] = 'S';
	else if (cmd[i] == '\"')
		token_string[i] = 'D';
	i++;
	while (cmd[i] != c && cmd[i] != '\0' && cmd[i] != '\n')
	{
		token_string[i] = 'A';
		i++;
	}
	if (cmd[i] == '\'')
		token_string[i] = 'S';
	else if (cmd[i] == '\"')
		token_string[i] = 'D';
	else if (cmd[i] == '\n')
		token_string[i] = '0';
	if (cmd[i] != '\0')
		i++;
	return (i);
}

int normal_tokenizer(char *cmd, int i, char *token_string)
{
	while (cmd[i] != '\0' && cmd[i] != ' ' && !ft_is_redirection(cmd[i]) && cmd[i] != '|')
	{
		if (cmd[i] == '\'' || cmd[i] == '"')
			i = quote_tokenizer(cmd, i, token_string, cmd[i]);
		else
		{
			token_string[i] = 'A';
			i++;
		}
	}
	return (i);
}

char	*tokenizer(char *cmd)
{
	int		i;
	char	*token_string;

	i = 0;
	token_string = malloc(sizeof(char) * (ft_strlen(cmd) + 1));
	token_string[ft_strlen(cmd)] = '\0';
	while (cmd[i] != '\0')
	{
		if (ft_is_redirection(cmd[i]))
			i = redirection_tokenizer(cmd, i, token_string, cmd[i]);
		else if (cmd[i] == '|')
			i = pipe_tokenizer(i, token_string);
		else if (cmd[i] == ' ' || cmd[i] == '\0')
			i = space_tokenizer(i, cmd, token_string);
		else if (cmd[i] != '\0')
			i = normal_tokenizer(cmd, i, token_string);
		else if (cmd[i] == '\0')
			break;
	}
	return (token_string);
}
