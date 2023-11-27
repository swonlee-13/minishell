/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:03:24 by yeolee2           #+#    #+#             */
/*   Updated: 2023/11/27 09:23:21 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	build_env(char ***env);
char** build_vector(const char* arg);

void	add_env_data(char ***env, char *path)
{
	char	**res;
	size_t	len;

	len = ft_strslen(*env) + 1;
	res = malloc(sizeof(char *) * (len + 1));
	//TODO: Return an error code
	if (!res)
		return ;
	ft_memcpy(res, *env, sizeof(char *) * ft_strslen(*env));
	res[len - 1] = ft_strdup(path);
	res[len] = NULL;
	free(*env);
	*env = res;
}

void    set_export_attribute(char ***env, char *path)
{
	int     idx;
	int		len;

	len = 0;
	while (path[len] && path[len] != '=')
		len++;
	idx = 0;
	while ((*env)[idx])
	{
		if (!ft_strncmp((*env)[idx], path, len))
		{
			free((*env)[idx]);
			(*env)[idx] = ft_strdup(path);
			break ;
		}
		idx++;
	}
	if (!(*env)[idx])
		add_env_data(env, path);
}

// #include <string.h>

// int main(void)
// {
//     char    **env;
// 	char** vector = malloc(3 * sizeof(char *));
	
// 	vector[0] = strdup("export");
// 	vector[1] = strdup("PATH=/Users/iyeonjae/Desktop/minishell/srcs");
// 	vector[2] = NULL;
// 	env = malloc(3 * sizeof(char *));
// 	build_env(&env);
//     printf("Before set_export_attribute:\n");
// 	for (int i = 0; env[i]; i++)
// 		printf("%s\n", env[i]);
// 	if (!ft_strcmp(vector[0], "export"))
// 	    set_export_attribute(&env, vector[1]);
//     printf("After set_export_attribute:\n");
// 	for (int i = 0; env[i]; i++)
// 		printf("%s\n", env[i]);
//     return 0;
// }
