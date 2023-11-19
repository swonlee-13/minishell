/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 23:49:35 by seongwol          #+#    #+#             */
/*   Updated: 2023/08/04 13:58:47 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free_index(char **strs, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

static const char	*ft_cut_length(char const *str, char c, size_t *len)
{
	while (*str && *str == c)
		str++;
	while (*(str + *len) && *(str + *len) != c)
		(*len)++;
	return (str);
}

static int	ft_word_count(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}	
		else
			i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char			**strs;
	size_t			index;
	const size_t	count = ft_word_count(s, c);
	size_t			len;

	index = 0;
	strs = (char **)ft_calloc(sizeof(char *), count + 1);
	if (strs == 0)
		ft_error("split failed");
	while (index < count)
	{
		len = 0;
		s = ft_cut_length(s, c, &len);
		strs[index] = ft_substr(s, 0, len);
		if (!strs[index])
		{
			ft_free_index(strs, index);
			ft_error("malloc failed");
		}
		s += len + 1;
		index++;
	}
	if (strs[0] == NULL)
		return (ft_free_index(strs, 0));
	return (strs);
}
