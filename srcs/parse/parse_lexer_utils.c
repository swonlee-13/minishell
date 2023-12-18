/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lexer_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <seongwol@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 18:49:09 by seongwol          #+#    #+#             */
/*   Updated: 2023/12/18 16:53:05 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	file_lexer_argument_check(char *token_string, int i, char c)
{
	while (token_string[i] == c)
		i++;
	while (token_string[i] == ' ')
		i++;
	if (token_string[i] != 'S' && token_string[i] != 'D' && \
		token_string[i] != 'A')
		return (SYNTAX_ERROR);
	else
		return (i);
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
