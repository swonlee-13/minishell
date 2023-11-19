/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 01:42:16 by seongwol          #+#    #+#             */
/*   Updated: 2023/03/25 05:59:42 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_find(const char *s1, const char *s2)
{
	size_t	index;

	index = 0;
	while (s2[index])
	{
		if (s1[index] != s2[index])
			return (0);
		index++;
	}
	return (1);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	needle_len;

	i = 0;
	needle_len = ft_strlen(needle);
	if (*needle == 0)
		return ((char *)haystack);
	while (haystack[i] && i + needle_len <= len)
	{
		if (haystack[i] == needle[0])
		{
			if (ft_find(haystack + i, needle))
				return ((char *)haystack + i);
		}
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>
int main()
{
	char *haystack = "42seoulleeseongwon";
	char *needle = "ees";

	printf(strnstr(haystack, needle, 15));
}
*/
