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

/*
int main()
{
	char *strsrc = "babobabo";
	char strdest[10] = "lol";

	printf("바뀌기 전 dest 주소 : %p\n", strdest);
	printf("바뀌고 난 dest 주소 : %p\n", ft_memcpy(strdest, strsrc, 5));
	printf("바뀌고 난 뒤 dest 문자열 : %s\n", strdest);

	char *strsrc1 = "babobabo";
	char strdest1[10] = "lol";

	printf("바뀌기 전 dest1 주소 : %p\n", strdest1);
	printf("바뀌고 난 dest1 주소 : %p\n", memcpy(strdest1, strsrc1, 5));
	printf("바뀌고 난 뒤 dest 문자열 : %s\n", strdest1);
}
*/
