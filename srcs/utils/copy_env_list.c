/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 19:22:52 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/11 22:52:12 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env_list(char **env)
{
	char		**ret;
	int			idx;
	const int	len = ft_strslen(env);

	idx = 0;
	ret = (char **)malloc(sizeof(char *) * (len + 1));
	while (idx < len)
	{
		ret[idx] = ft_strdup(env[idx]);
		idx++;
	}
	ret[idx] = NULL;
	return (ret);
}
