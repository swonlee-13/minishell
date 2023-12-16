/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <seongwol@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 18:48:56 by seongwol          #+#    #+#             */
/*   Updated: 2023/12/16 18:52:05 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

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

int	token_lexer(char *cmd, char *token_string)
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
