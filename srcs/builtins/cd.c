/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 01:05:18 by yeolee2           #+#    #+#             */
/*   Updated: 2023/11/25 00:56:18 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <string.h>

char    *get_env(char **env, char *str)
{
    int     idx;
    char    *res;

    idx = 0;
    while (env[idx])
    {
        //TODO: Is it okay to use strncmp when searching for the env variable?
        if (!ft_strncmp(str, env[idx], ft_strlen(str)) && env[idx][ft_strlen(str) + 1] == '=')
            break;
        idx++;
    }
    return (env[idx]);
}

void    change_directory(char **vector, char **env)
{
    char    *curr_directory;
    char    *prev_directory;
    char    *targ_directory;

    //TODO: prev_directory should check OLDPWD
    if (find_env(env, "OLDPWD"))
        prev_directory = NULL;
    targ_directory = vector[1];
    //TODO: How to initialize curr_directory
    if (getcwd(curr_directory, PATH_MAX))
        printf("%s\n", curr_directory);
        // curr_directory = NULL;
    if (!vector[1])
        targ_directory = getenv("HOME");
    else if (!ft_strcmp(vector[1], "-"))
    {
        // If OLDPWD not set, print error message.
        if (!prev_directory)
            printf("minishell: cd: OLDPWD not set\n");
        else
        {
            printf("%s\n", prev_directory);
            targ_directory = prev_directory;
        }
    }
    //TODO: SUCCESS MACRO
    if (!chdir(targ_directory))
    {
        prev_directory = curr_directory;
        getcwd(curr_directory, PATH_MAX);
    }
    else
        printf("minishell: cd: %s: No such file or directory\n", vector[1]);
    //TODO: Modify PWD and OLDPWD with curr_directory and prev_directory
}

char** build_vector(const char* arg)
{
    char** vector = malloc(3 * sizeof(char *));
    vector[0] = strdup("cd");  // First argument is usually the command name
    vector[1] = strdup(arg);
    vector[2] = NULL;  // Argument list must be NULL terminated
    return vector;
}

void free_vector(char** vector) {
    free(vector[0]);
    free(vector[1]);
    free(vector);
}

int main(void)
{
    char    *dir;
    char    **env;
    char    **vector;

    printf("-----------------------------------------\n");
    vector = build_vector("/Users/iyeonjae/Desktop/minishell/srcs");
    change_directory(vector, env);
    free_vector(vector);
    printf("dir: %s\n", getcwd(dir, PATH_MAX));
    printf("-----------------------------------------\n");
    vector = build_vector("builtins");
    change_directory(vector, env);
    free_vector(vector);
    printf("dir: %s\n", getcwd(dir, PATH_MAX));
    printf("-----------------------------------------\n");
    vector = build_vector("-");
    change_directory(vector, env);
    free_vector(vector);
    printf("dir: %s\n", getcwd(dir, PATH_MAX));
    printf("-----------------------------------------\n");
    vector = build_vector("/");
    change_directory(vector, env);
    free_vector(vector);
    printf("dir: %s\n", getcwd(dir, PATH_MAX));
    printf("-----------------------------------------\n");
}
