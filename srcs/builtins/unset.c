/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:10:28 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/24 15:30:12 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

int	check_bash_var_name_convention(char *name)
{
	size_t	idx;

	if (name[0] == '\0' || ft_isdigit(name[0]))
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

static void	handle_unset_error(char *name)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin("`", name);
	res = ft_strjoin(tmp, "'");
	free(tmp);
	print_error_complex("unset", res, "not a valid identifier");
	free(res);
	g_exit_code = 1;
	return ;
}

void	remove_env_data(char ***env, char *name)
{
	int		len;
	char	**res;
	size_t	i;
	size_t	j;

	if (check_bash_var_name_convention(name) == FAILURE)
		return (handle_unset_error(name));
	if (get_env_data(*env, name) == NULL)
		return ;
	len = ft_strlen(name);
	res = malloc(sizeof(char *) * ft_strslen(*env));
	if (!res)
		return ;
	i = -1;
	j = 0;
	while ((*env)[++i])
	{
		if (!ft_strncmp(name, (*env)[i], len) \
			&& ((*env)[i][len] == '=' || (*env)[i][len] == '\0'))
			continue ;
		res[j++] = ft_strdup((*env)[i]);
	}
	res[j] = NULL;
	ft_free(*env);
	*env = res;
}

void	unset_export_attribute(char ***env, char **vector)
{
	int		idx;
	int		flag;
	char	*name;

	flag = 0;
	if (vector[1] == NULL)
	{
		g_exit_code = 0;
		return ;
	}
	idx = 1;
	while (vector[idx])
	{
		name = ft_substr(vector[idx], 0, ft_strlen(vector[idx]));
		remove_env_data(env, name);
		if (g_exit_code == 1)
			flag = 1;
		free(name);
		idx++;
	}
	g_exit_code = flag;
}
