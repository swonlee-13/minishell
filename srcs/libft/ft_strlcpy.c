/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 04:19:36 by seongwol          #+#    #+#             */
/*   Updated: 2023/03/22 05:40:19 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	index;

	index = 0;
	while (src[index] && index + 1 < dstsize)
	{
		dst[index] = src[index];
		index++;
	}
	if (dstsize != 0)
		dst[index] = 0;
	return (ft_strlen(src));
}
