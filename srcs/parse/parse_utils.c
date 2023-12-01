/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 19:22:25 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/01 19:22:28 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

int	ft_is_pipe(char c)
{
	if (c == '|')
		return (1);
	else
		return (0);
}

int	ft_is_invalid(char c)
{
	if (c == '&' || c == '{' || c == '}')
		return (1);
	else
		return (0);
}

int	ft_is_meta(char c)
{
	if (c == ' ' || c == '\"' || c == '\'' | c == '$')
		return (TRUE);
	else
		return (FALSE);
}

int	ft_is_redirection(char c)
{
	if (c == '<' || c == '>')
		return (TRUE);
	return (FALSE);
}

int	ft_is_op_token(char c)
{
	if (c == 'P' || c == 'I' || c == 'O')
		return (TRUE);
	else if (c == ' ')
		return (TRUE);
	return (FALSE);
}

int	ft_is_op_redirection(char c)
{
	if (c == 'I' || c == 'O')
		return (TRUE);
	else
		return (FALSE);
}
