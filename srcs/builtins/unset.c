/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:10:28 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/15 19:58:10 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

static int	check_bash_var_name_convention(char *name)
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

static void	handle_unset_error(char *name)
{
	printf("minishell: unset: %s: not a valid identifier\n", name);
	g_exit_code = 1;
	return ;
}

void	remove_env_data(char ***env, char *name)
{
	char	**res;
	size_t	i;
	size_t	j;

	if (!get_env_data(*env, name))
		return ;
	if (check_bash_var_name_convention(name) == FAILURE)
		return (handle_unset_error(name));
	res = malloc(sizeof(char *) * (ft_strslen(*env) - 1));
	if (!res)
		return ;
	i = -1;
	j = 0;
	while ((*env)[++i])
	{
		if (!ft_strncmp(name, (*env)[i], ft_strlen(name)) \
			&& (*env)[i][ft_strlen(name)] == '=')
			continue ;
		res[j++] = ft_strdup((*env)[i]);
	}
	res[j] = NULL;
	ft_free(*env);
	*env = res;
}
