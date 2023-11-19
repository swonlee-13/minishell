/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <seongwol@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 04:59:32 by seongwol          #+#    #+#             */
/*   Updated: 2023/04/27 03:45:33 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char			*b1;
	unsigned char	c1;

	b1 = (char *)b;
	c1 = (unsigned char)c;
	while (len > 0)
	{
		*b1 = c1;
		b1++;
		len--;
	}
	return (b);
}
