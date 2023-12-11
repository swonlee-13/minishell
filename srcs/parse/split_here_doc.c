/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 22:37:52 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/11 22:37:53 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	split_indexing(char *str, int i)
{
	if (str[i] == '$' && str[i + 1] == '?')
		return (i + 1);
	if (str[i] == '$')
	{
		i++;
		if (str[i] != '_' && !ft_isalpha(str[i]))
			return (i - 1);
		while (ft_isalnum(str[i]) || str[i] == '_')
			i++;
	}
	else
	{
		while (str[i] != '$' && str[i] != '\0')
			i++;
	}
	return (i - 1);
}

static int	line_count(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		i = split_indexing(str, i);
		count++;
		i++; 
	}
	return (count);
}

char	**shell_split_here_doc(char *str)
{
	char		**res;
	const int	word = line_count(str);
	int			i;
	int			start;
	int			end;

	res = (char **)malloc(sizeof(char *) * (word + 1));
	i = 0;
	start = 0;
	while (i < word)
	{
		end = split_indexing(str, start);
		res[i] = ft_substr(str, start, end - start + 1);
		start = end + 1;
		i++;
	}
	res[word] = NULL;
	return (res);
}
