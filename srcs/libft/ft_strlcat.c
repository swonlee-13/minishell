/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 04:20:22 by seongwol          #+#    #+#             */
/*   Updated: 2023/07/07 16:34:31 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	srclen;
	size_t	dstlen;

	i = 0;
	srclen = ft_strlen(src);
	dstlen = ft_strlen(dst);
	if (dstlen >= dstsize)
		return (dstsize + srclen);
	while (*dst && i + 1 < dstsize)
	{
		i++;
		dst++;
	}
	while (i + 1 < dstsize && *src)
	{
		*dst = *src;
		i++;
		src++;
		dst++;
	}
	*dst = 0;
	return (dstlen + srclen);
}
