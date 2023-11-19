/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 01:29:44 by seongwol          #+#    #+#             */
/*   Updated: 2023/03/26 22:17:43 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*copy_dst;
	unsigned char	*copy_src;

	copy_dst = (unsigned char *)dst;
	copy_src = (unsigned char *)src;
	if (copy_dst > copy_src)
	{
		copy_dst += len - 1;
		copy_src += len - 1;
		while (len > 0)
		{
			*copy_dst = *copy_src;
			copy_dst--;
			copy_src--;
			len--;
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
