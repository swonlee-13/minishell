/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <seongwol@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 19:14:32 by seongwol          #+#    #+#             */
/*   Updated: 2023/12/16 19:14:33 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

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
