/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 02:51:10 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/14 02:22:08 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    print_working_directory(void)
{
    char    *pwd;

    pwd = getcwd(NULL, 0);
    if (pwd == NULL)
    {
        printf("%s\n", strerror(errno));
        free(pwd);
    }
    printf("%s\n", pwd);
    free(pwd);
}
