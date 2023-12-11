/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:10:28 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/11 22:42:11 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #include <string.h>

// char    *get_env(char **env, char *str);
// void	build_env(char ***env);

int	check_bash_var_name_convention(char *name)
{
	size_t	idx;

	if (ft_isdigit(name[0]))
		return (FAILURE);
	idx = 0;
	while (name[idx])
	{
		if (!(ft_isalnum(name[idx]) || name[idx] == '_'))
			return (FAILURE);
		idx++;
	}
	return (SUCCESS);
}

void	remove_env_data(char ***env, char *name)
{
	char	**res;
	size_t	i;
	size_t  j;

	if (!get_env(*env, name))
		return ;
	if (check_bash_var_name_convention(name) == FAILURE)
	{
		printf("minishell: unset: %s: not a valid identifier", name);
		return ;
	}
	res = malloc(sizeof(char *) * (ft_strslen(*env) - 1));
	if (!res)
		return ;
	i = -1;
	j = 0;
	while ((*env)[++i])
	{
		if (ft_strncmp(name, (*env)[i], ft_strlen(name)) && (*env)[i][ft_strlen(name)] == '=')
			res[j++] = ft_strdup((*env)[i]);
		else
			free((*env)[i]);
	}
	res[j] = NULL;
	*env = res;
}

// int main(void)
// {
//     char    **env;
// 	char** vector = malloc(3 * sizeof(char *));
	
// 	vector[0] = strdup("unset");
// 	vector[1] = strdup("PATH");
// 	vector[2] = NULL;
// 	env = malloc(3 * sizeof(char *));
// 	build_env(&env);
//     printf("Before remove_env_data:\n");
// 	for (int i = 0; env[i]; i++)
// 		printf("%s\n", env[i]);
// 	if (!ft_strcmp(vector[0], "unset"))
// 	    remove_env_data(&env, vector[1]);
//     printf("After remove_env_data:\n");
// 	for (int i = 0; env[i]; i++)
// 		printf("%s\n", env[i]);
//     return 0;
// }
