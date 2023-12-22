/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:10:28 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/22 15:19:18 by yeolee2          ###   ########.fr       */
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
	print_error_complex("unset", name, "not a valid identifier");
	g_exit_code = 1;
	return ;
}

void	remove_env_data(char ***env, char *name)
{
	char	**res;
	size_t	i;
	size_t	j;

	if (get_env_data(*env, name) == NULL)
		return ;
	if (check_bash_var_name_convention(name) == FAILURE)
		return (handle_unset_error(name));
	res = malloc(sizeof(char *) * ft_strslen(*env));
	if (!res)
		return ;
	i = -1;
	j = 0;
	while ((*env)[++i])
	{
		if (!ft_strncmp(name, (*env)[i], ft_strlen(name)) \
			&& ((*env)[i][ft_strlen(name)] == '=' || (*env)[i][ft_strlen(name)] == '\0'))
			continue ;
		res[j++] = ft_strdup((*env)[i]);
	}
	res[j] = NULL;
	ft_free(*env);
	*env = res;
}
