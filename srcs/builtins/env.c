/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 04:05:23 by yeolee2           #+#    #+#             */
/*   Updated: 2023/11/24 00:12:24 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    print_env_list(char **vector)
{
    size_t  idx;

    idx = 0;
    while (vector[idx])
    {
        ft_printf("%s\n", vector[idx]);
        idx++;
    }
}
