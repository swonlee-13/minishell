/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 04:05:23 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/15 19:51:57 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	print_env_list(char **env)
{
	size_t	idx;

	idx = 0;
	while (env[idx])
	{
		if (ft_strchr(env[idx], '='))
			printf("%s\n", env[idx]);
		idx++;
	}
	g_exit_code = 0;
}
