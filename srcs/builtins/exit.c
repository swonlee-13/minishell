/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:10:20 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/16 21:04:48 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

static int	check_exit_arg(char *arg)
{
	int		idx;

	idx = 0;
	while (arg[idx])
	{
		if (!ft_isdigit(arg[idx]))
		{
			g_exit_code = 255;
			printf("minishell: exit: %s: numeric argument required\n", arg);
			exit(g_exit_code);
		}
	}
	return (SUCCESS);
}

void	terminate_program(char **vector)
{
	printf("exit\n");
	if (vector[1] == NULL)
		exit(EXIT_SUCCESS);
	if (check_exit_arg(vector[1]) == SUCCESS)
	{
		g_exit_code = ft_atoi(vector[1]);
		if (ft_strslen(vector) > 1)
		{
			g_exit_code = 1;
			printf("minishell: exit: too many arguments\n");
			return ;
		}
		else
			exit(g_exit_code);
	}
}
