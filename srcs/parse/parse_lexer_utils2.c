/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lexer_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <seongwol@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 18:50:11 by seongwol          #+#    #+#             */
/*   Updated: 2023/12/18 16:55:45 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dollar_sign_lexer_quote(char *cmd, int i)
{
	i++;
	while (cmd[i] != '\'')
		i++;
	return (i + 1);
}

int	dollar_sign_lexer_double(char *cmd, int i)
{
	i++;
	if (cmd[i] == '$')
		return (SYNTAX_ERROR);
	if (cmd[i] == ' ' || cmd[i] == '\0' || cmd[i] == '\'')
		return (i);
	if ((cmd[i] != '?' && cmd[i] != '"') && (!ft_isalpha(cmd[i]) \
				&& cmd[i] != '_'))
		return (SYNTAX_ERROR);
	else
		return (i);
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
