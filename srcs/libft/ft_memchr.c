/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 17:03:09 by seongwol          #+#    #+#             */
/*   Updated: 2023/03/22 05:42:19 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*copy_s;
	unsigned char	copy_c;
	size_t			index;

	copy_s = (unsigned char *)s;
	copy_c = (unsigned char)c;
	index = 0;
	while (index < n)
	{
		if (*copy_s == copy_c)
			break ;
		copy_s++;
		index++;
	}
	if (index == n)
		return (0);
	else
		return ((void *)copy_s);
}
/*
int main()
{
   printf("%s\n", (char *)memchr("bonjorlaksnd", 'n', 2)); 
   printf("%s\n", (char *)ft_memchr("bonjorlaksnd", 'n', 2)); 
   printf("%s\n", (char *)ft_memchr("42seoul", 'e', 2)); 
}
*/
