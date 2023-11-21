/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 20:36:18 by seongwol          #+#    #+#             */
/*   Updated: 2023/11/22 02:17:36 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static int	count_len(char **strs)
// {
// 	int	i;

// 	i = 0;
// 	if(strs)
// 		while (strs[i] != NULL)
// 			i++;
// 	return (i);
// }

void	ft_free(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}
