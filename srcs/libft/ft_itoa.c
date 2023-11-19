/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:33:17 by seongwol          #+#    #+#             */
/*   Updated: 2023/04/11 05:33:25 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_rev_sort(char *str)
{
	size_t	i;
	size_t	j;
	char	temp;

	i = 0;
	j = ft_strlen(str) - 1;
	while (i < j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
	return (str);
}

static int	ft_count_digit(int n)
{
	unsigned int	len;

	len = 0;
	if (n < 0)
		n *= -1;
	if (n == 0)
		len++;
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		index;
	int		digit;

	digit = ft_count_digit(n);
	index = -1;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	else if (n < 0)
	{
		n *= -1;
		res = ft_calloc(sizeof(char), digit + 2);
		if (res)
			res[digit] = '-';
	}
	else
		res = ft_calloc(sizeof(char), digit + 1);
	if (!res)
		return (NULL);
	while (++index < digit)
	{
		res[index] = n % 10 + '0';
		n = n / 10;
	}
	return (ft_rev_sort(res));
}
