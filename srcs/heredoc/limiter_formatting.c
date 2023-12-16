/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limiter_formatting.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <seongwol@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 19:56:58 by seongwol          #+#    #+#             */
/*   Updated: 2023/12/16 19:57:02 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*limiter_formatting(char *data)
{
	char	*res;

	if (data[0] == '"')
		res = ft_strtrim(data, "\"");
	else if (data[0] == '\'')
		res = ft_strtrim(data, "'");
	else
		res = ft_strdup(data);
	free(data);
	return (res);
}