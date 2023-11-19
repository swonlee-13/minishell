/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:04:14 by seongwol          #+#    #+#             */
/*   Updated: 2023/04/05 03:13:32 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	index;
	char	*copy;

	index = 0;
	if (len + start > ft_strlen(s))
		len = ft_strlen(s) - start;
	if (start > ft_strlen(s))
		len = 0;
	copy = malloc(len + 1);
	if (!copy)
		return (NULL);
	if (start <= ft_strlen(s))
	{
		while (index < len)
		{
			*(copy + index) = *(s + start + index);
			index++;
		}
	}
	copy[index] = 0;
	return (copy);
}
