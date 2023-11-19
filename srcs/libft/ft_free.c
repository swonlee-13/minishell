/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 20:36:18 by seongwol          #+#    #+#             */
/*   Updated: 2023/08/03 20:37:37 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_len(char **strs)
{
	int	i;

	i = 0;
	if(strs)
		while (strs[i] != NULL)
			i++;
	return (i);
}

void	ft_free(char **strs)
{
	int	i;
	int	len;

	i = 0;
	len = count_len(strs);
	while (i < len)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}
