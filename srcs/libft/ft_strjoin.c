/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:39:51 by seongwol          #+#    #+#             */
/*   Updated: 2023/08/04 02:00:39 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	index;
	char	*copy;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	index = 0;
	copy = ft_calloc(sizeof(char), (s1_len + s2_len + 1));
	if (!copy)
		return (NULL);
	while (index < s1_len + s2_len + 1)
	{
		copy[index] = 0;
		index++;
	}
	if (s1 != NULL)
		ft_strlcat(copy, s1, s1_len + s2_len + 1);
	ft_strlcat(copy, s2, s1_len + s2_len + 1);
	return (copy);
}
