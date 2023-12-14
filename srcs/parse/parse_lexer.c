/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 19:21:52 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/14 02:02:52 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	redir_lexer_count(char *token_string, int i, char c)
{
	int	res;

	res = 0;
	while (token_string[i] == c)
	{
		res++;
		i++;
	}
	if (res > 2)
		return (SYNTAX_ERROR);
	return (i);
}

int	redir_lexer(char *token_string)
{
	int	i;

	i = 0;
	while (token_string[i])
	{
		if (token_string[i] == 'I' || token_string[i] == 'O')
		{
			i = redir_lexer_count(token_string, i, token_string[i]);
			if (i == SYNTAX_ERROR)
			{
				write(2, "minishell: redirection ", 23);
				return (SYNTAX_ERROR);
			}
			if (token_string[i] == 'I' || token_string[i] == 'O')
			{
				write(2, "minishell: redirection ", 23);
				return (SYNTAX_ERROR);
			}
		}
		else
			i++;
	}
	return (TRUE);
}

int	quote_lexer_find_end(char *token_string, int i, char c)
{
	i++;
	while (token_string[i] != '\0' && token_string[i] != c)
	{
		i++;
	}
	if (token_string[i] != c)
		return (SYNTAX_ERROR);
	else
		return (i + 1);
}

int	quote_lexer(char *token_string)
{
	int	i;

	i = 0;
	while (token_string[i])
	{
		if (token_string[i] == 'S' || token_string[i] == 'D')
		{
			i = quote_lexer_find_end(token_string, i, token_string[i]);
			if (i == SYNTAX_ERROR)
			{
				write(2, "minishell: quote ", 17);
				return (SYNTAX_ERROR);
			}
		}
		else
			i++;
	}
	return (TRUE);
}

int	file_lexer_argument_check(char *token_string, int i, char c)
{
	while (token_string[i] == c)
		i++;
	while (token_string[i] == ' ')
		i++;
	if (token_string[i] != 'S' && token_string[i] != 'D' && token_string[i] != 'A')
		return (SYNTAX_ERROR);
	else
		return (i);
}

int	file_lexer(char *token_string)
{
	int	i;

	i = 0;
	while (token_string[i])
	{
		if (token_string[i] == 'I' || token_string[i] == 'O')
		{
			i = file_lexer_argument_check(token_string, i, token_string[i]);
			if (i == SYNTAX_ERROR)
			{
				write(2, "minishell: file ", 16);
				return (SYNTAX_ERROR);
			}
		}
		else
			i++;
	}
	return (TRUE);
}

int	pipe_lexer_double_check(char *token_string, int i)
{
	i++;
	while (token_string[i] == ' ')
		i++;
	if (token_string[i] == 'P' || token_string[i] == '\0')
		return (SYNTAX_ERROR);
	else
		return (i);
}

int	pipe_lexer(char *token_string)
{
	int	i;

	i = 0;
	while (token_string[i])
	{
		if (token_string[0] == 'P')
		{
			write(2, "minishell: pipe ", 16);
			return (SYNTAX_ERROR);
		}
		if (token_string[i] == 'P')
		{
			i = pipe_lexer_double_check(token_string, i);
			if (i == SYNTAX_ERROR)
			{
				write(2, "minishell: pipe ", 16);
				return (SYNTAX_ERROR);
			}
		}
		else
			i++;
	}
	return (TRUE);
}

int	dollar_sign_lexer_double(char *cmd, int i)
{
	i++;
	if (cmd[i] == '$')
		return (SYNTAX_ERROR);
	if (cmd[i] == ' ' || cmd[i] == '\0')
		return (i);
	if ((cmd[i] != '?' && cmd[i] != '"') && (!ft_isalpha(cmd[i]) && cmd[i] != '_'))
		return (SYNTAX_ERROR);
	else
		return (i);
}

int	dollar_sign_lexer_quote(char *cmd, int i)
{
	i++;
	while (cmd[i] != '\'')
		i++;
	return (i + 1);
}

int	dollar_sign_lexer(char *cmd, char *token_string)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' && token_string[i] == 'S')
			i = dollar_sign_lexer_quote(cmd, i);
		else if (cmd[i] == '$')
		{
			i = dollar_sign_lexer_double(cmd, i);
			if (i == SYNTAX_ERROR)
			{
				write(2, "minishell: dollar sign ", 23);
				return (SYNTAX_ERROR);
			}
		}
		else
			i++;
	}
	return (TRUE);
}

int token_lexer(char *cmd, char *token_string)
{
	if (redir_lexer(token_string) == SYNTAX_ERROR)
		return (SYNTAX_ERROR);
	if (quote_lexer(token_string) == SYNTAX_ERROR)
		return (SYNTAX_ERROR);
	if (file_lexer(token_string) == SYNTAX_ERROR)
		return (SYNTAX_ERROR);
	if (pipe_lexer(token_string) == SYNTAX_ERROR)
		return (SYNTAX_ERROR);
	if (dollar_sign_lexer(cmd, token_string) == SYNTAX_ERROR)
		return (SYNTAX_ERROR);
	return (TRUE);
}
