/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 22:26:07 by seongwol          #+#    #+#             */
/*   Updated: 2023/03/26 22:15:20 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			index;
	unsigned char	*copy_src;
	unsigned char	*copy_dst;

	index = 0;
	copy_src = (unsigned char *)src;
	copy_dst = (unsigned char *)dst;
	if (src == dst)
		return (0);
	while (index < n)
	{
		*copy_dst = *copy_src;
		copy_dst++;
		copy_src++;
		index++;
	}
	return (dst);
}
