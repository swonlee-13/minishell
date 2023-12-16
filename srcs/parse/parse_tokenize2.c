/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokenize2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <seongwol@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 19:09:32 by seongwol          #+#    #+#             */
/*   Updated: 2023/12/16 19:25:04 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	pipe_tokenizer(int i, char *token_string)
{
	token_string[i] = 'P';
	return (i + 1);
}
