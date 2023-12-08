/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 22:32:36 by seongwol          #+#    #+#             */
/*   Updated: 2023/12/08 16:54:37 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_freee(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

static int	ft_index(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		return (-2);
	return (i);
}

static char	*ft_output(char **storage)
{
	char	*ret;
	char	*temp;

	if (!*storage)
		return (NULL);
	if (*storage && **storage == 0)
		return (ft_freee(storage));
	temp = *storage;
	ret = ft_substr(temp, 0, ft_index(temp) + 1);
	if (!ret)
		return (ft_freee(storage));
	if (ft_index(temp) >= 0)
	{
		*storage = ft_substr(temp, ft_index(temp) + 1, ft_strlen(temp));
		free(temp);
		if (!*storage)
			return (ft_freee(&ret));
	}
	else
	{
		free(*storage);
		*storage = NULL;
	}
	return (ret);
}

static int	ft_input(char **storage, char *buffer)
{
	char	*temp;

	temp = *storage;
	*storage = ft_strjoin(*storage, buffer);
	free(temp);
	if (!*storage)
		return (0);
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		buffer[BUFFER_SIZE + 1];
	int			read_size;
	int			checker;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		read_size = read(fd, buffer, BUFFER_SIZE);
		if (read_size == -1)
			return (ft_freee(&storage));
		if (read_size == 0)
			break ;
		buffer[read_size] = '\0';
		checker = ft_input(&storage, buffer);
		if (checker == 0)
			return (NULL);
		if (ft_index(buffer) >= 0)
			break ;
	}
	return (ft_output(&storage));
}
