/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:52:51 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/11 23:02:01 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_the_rest_of_arg(char *arg)
{
    size_t  idx;

    idx = 0;
    while (arg[idx])
    {
        if (arg[idx] != 'n')
            return (FAILURE);
        idx++;
    }
    return (SUCCESS);
}

int is_n_option(char *arg)
{
    size_t  idx;

    idx = 0;
    while (arg[idx])
    {
        if (!ft_strncmp(&arg[idx], "-n", 2))
        {
            if (check_the_rest_of_arg(&arg[idx] + 2) == SUCCESS)
                return (TRUE);
        }
        idx++;
    }
    return (FALSE);
}

void    write_arg_to_stdout(char **vector)
{
    int idx;

    idx = 1;
    if (vector[1] == NULL)
    {
        printf("\n");
        return ;
    }
    while (is_n_option(vector[idx]) == TRUE)
        idx++;
    while (vector[idx])
    {
        printf("%s", vector[idx]);
        if (vector[idx + 1])
            printf(" ");
        idx++;
    }
    if (is_n_option(vector[1]) == FALSE)
        printf("\n");
}

// #include <string.h>

// int main(void)
// {
//     char    **env;
// 	char** vector = malloc(5 * sizeof(char *));
	
// 	vector[0] = strdup("echo");
// 	vector[1] = strdup("-f");
// 	vector[2] = strdup("-n");
// 	vector[3] = strdup("-g");
// 	vector[4] = strdup("-h");
// 	if (!ft_strcmp(vector[0], "echo"))
// 	    write_arg_to_stdout(vector);
//     return 0;
// }
