/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:57:30 by seongwol          #+#    #+#             */
/*   Updated: 2023/03/22 05:35:28 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*copy1;
	unsigned char	*copy2;
	size_t			index;

	copy1 = (unsigned char *)s1;
	copy2 = (unsigned char *)s2;
	index = 0;
	if (n == 0)
		return (0);
	while ((*copy1 == *copy2 && copy1) && index + 1 < n)
	{
		copy1++;
		copy2++;
		index++;
	}
	return ((unsigned char)*copy1 - (unsigned char)*copy2);
}
