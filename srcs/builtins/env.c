/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 04:05:23 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/14 01:05:29 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_exit_code;

void    print_env_list(char **env)
{
	size_t  idx;

	idx = 0;
	while (env[idx])
	{
		printf("%s\n", env[idx]);
		idx++;
	}
	g_exit_code = 0;
}
