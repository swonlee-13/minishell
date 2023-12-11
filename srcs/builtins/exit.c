/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:10:20 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/12 00:45:25 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_exit_code;

int    check_exit_arg(char **vector)
{
    int     idx;
    char    *arg;
    
    arg = vector[0];
    idx = 0;
    while (arg[idx])
    {
        if (!ft_isdigit(arg[idx]))
        {
            g_exit_code = 255;
            print_error_message(vector, "numeric argument required\n");
            exit(g_exit_code);
        }
    }
    return (SUCCESS);
}

void    terminate_program(char **vector)
{
    if (vector[1] == NULL)
        exit(EXIT_SUCCESS);
    if (ft_strslen(vector) == 2)
    {
        g_exit_code = ft_atoi(vector[1]);
        if (g_exit_code == 0)
        {
            if (check_exit_arg(vector) == SUCCESS)
                exit(g_exit_code);
        }
        else
            exit(g_exit_code);
    }
    g_exit_code = 1;
}
