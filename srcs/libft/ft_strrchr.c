/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <seongwol@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 04:07:32 by seongwol          #+#    #+#             */
/*   Updated: 2023/03/22 05:39:31 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*s1;

	s1 = 0;
	while (*s != 0)
	{
		if (*s == (char)c)
			s1 = (char *)s;
		s++;
	}
	if ((char)c == 0)
		s1 = (char *)s;
	return (s1);
}
