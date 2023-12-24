/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 19:22:52 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/24 15:29:01 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env_list(char **env)
{
	char		**ret;
	int			idx;
	const int	len = ft_strslen(env);

	idx = 0;
	ret = (char **)malloc(sizeof(char *) * (len + 1));
	if (!ret)
		return (NULL);
	while (idx < len)
	{
		ret[idx] = ft_strdup(env[idx]);
		idx++;
	}
	ret[idx] = NULL;
	return (ret);
}

char	*get_env_data(char **env, char *str)
{
	int		idx;
	int		len;
	char	*res;

	len = ft_strlen(str);
	idx = 0;
	while (env[idx])
	{
		if (!ft_strncmp(str, env[idx], len) && \
			(env[idx][len] == '=' || env[idx][len] == '\0'))
		{
			res = env[idx];
			break ;
		}
		idx++;
	}
	if (env[idx] == NULL)
		return (NULL);
	if (ft_strchr(env[idx], '=') == NULL)
		return (res + len);
	while (*res != '=')
		res++;
	return (res + 1);
}

char	*set_env_name_and_value(char *name, char *path)
{
	char	*temp;

	if (path)
	{
		temp = ft_strjoin(name, path);
		free(path);
		return (temp);
	}
	return (NULL);
}

void	renew_env_data(char ***env, char *curr_dir, char *prev_dir)
{
	if (prev_dir)
	{
		prev_dir = set_env_name_and_value("OLDPWD=", prev_dir);
		set_each_attribute(env, prev_dir);
		free(prev_dir);
	}
	curr_dir = set_env_name_and_value("PWD=", curr_dir);
	set_each_attribute(env, curr_dir);
	free(curr_dir);
}

void	add_env_data(char ***env, char *path)
{
	char	**res;
	size_t	len;

	len = ft_strslen(*env) + 1;
	res = malloc(sizeof(char *) * (len + 1));
	if (!res)
		return ;
	ft_memcpy(res, *env, sizeof(char *) * ft_strslen(*env));
	res[len - 1] = ft_strdup(path);
	res[len] = NULL;
	free(*env);
	*env = res;
}
