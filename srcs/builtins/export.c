/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:03:24 by yeolee2           #+#    #+#             */
/*   Updated: 2023/11/25 01:13:29 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_env_data(char ***env, char *path)
{
	char	**res;
	size_t	len;

	len = ft_strslen(*env) + 1;
	res = malloc(sizeof(char *) * (len + 1));
	//FIXME: Return an error code
	if (!res)
		return ;
	ft_memcpy(res, *env, ft_strslen(*env));
	ft_memcpy(res[len], path, ft_strlen(path));
	res[len + 1] = NULL;
	free(*env);
	env = &res;
}

void    set_export_attribute(char **env, char **vector)
{
	int     idx;
	int		len;

	len = 0;
	//FIXME: What if vector[1] doesn't contain '='?
	while (vector[1][len] && vector[1][len] != '=')
		len++;
	idx = 0;
	while (env[idx])
	{
		if (!ft_strncmp(env[idx], vector[1], len))
		{
			free(env[idx]);
			//FIXME: The function always adds the new environment variable even if it replaces an existing one.
			env[idx] = ft_strdup(vector[1]);
			break ;
		}
		idx++;
	}
	if (idx == ft_strslen(env) + 1)
		add_env_data(&env, vector[1]);
}

int main(void)
{
    char *env[] = {"PATH=/usr/bin", "HOME=/home/user", NULL};
    char *vector[] = {"set", "HOME=/home/newuser", NULL};

    printf("Before set_export_attribute: HOME=%s\n", env[1]);
    set_export_attribute(env, vector);
    printf("After set_export_attribute: HOME=%s\n", env[1]);
    return 0;
}
