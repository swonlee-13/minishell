/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:43:41 by seongwol          #+#    #+#             */
/*   Updated: 2023/09/11 22:09:28 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isset(char c, char const *str)
{
	while (*str)
	{
		if (c == *str)
			return (1);
		str++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*copy;
	size_t		index;

	copy = 0;
	if (*s1 && *set)
	{
		while (*s1 && ft_isset(*s1, set))
			s1++;
		index = ft_strlen(s1);
		while (index > 0 && ft_isset(s1[index - 1], set))
			index--;
	}
	else
		index = ft_strlen(s1);
	copy = ft_calloc(1, index + 1);
	if (copy)
		ft_strlcat(copy, s1, index + 1);
	return (copy);
}
