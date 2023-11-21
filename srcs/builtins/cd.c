/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 01:05:18 by yeolee2           #+#    #+#             */
/*   Updated: 2023/11/22 03:50:40 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    change_directory(char **vector)
{
    char    *target;
    if (ft_strslen(vector) < 1)
    {
        //TODO: Adjusments of the errno be made
        perror("cd: Missing argument");
        return ;
    }
    target = vector[1];
    if (chdir(target) != 0)
        perror("cd: Failed to change directory");
}
