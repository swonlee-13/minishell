/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 17:19:56 by seongwol          #+#    #+#             */
/*   Updated: 2023/03/24 22:47:06 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	index;
	char			*res;

	index = ft_strlen(s);
	res = ft_calloc(1, index + 1);
	index = 0;
	if (!res)
		return (NULL);
	while (s[index])
	{
		res[index] = f(index, s[index]);
		index++;
	}
	return (res);
}
