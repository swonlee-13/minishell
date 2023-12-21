/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:03:24 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/19 05:31:12 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

static char	**sort_export_attribute(char **env)
{
	int		i;
	int		j;
	char	*tmp;
	char	**res;

	res = copy_env_list(env);
	i = 0;
	while (res[i + 1])
	{
		j = i + 1;
		while (res[j])
		{
			if (ft_strcmp(res[i], res[j]) > 0)
			{
				tmp = res[i];
				res[i] = res[j];
				res[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (res);
}

static void	print_export_attribute(char **env)
{
	int		i;
	int		j;
	char	**res;

	res = sort_export_attribute(env);
	i = -1;
	while (res[++i])
	{
		printf("declare -x ");
		j = -1;
		if (!ft_strchr(res[i], '='))
		{
			while (++j < (int)ft_strlen(res[i]))
				printf("%c", res[i][j]);
			printf("\n");
			continue ;
		}
		while (res[i][++j] != '=')
			printf("%c", res[i][j]);
		printf("=\"");
		while (res[i][++j])
			printf("%c", res[i][j]);
		printf("\"\n");
	}
	ft_free(res);
}

static void	handle_export_error(char *arg, char *name)
{
	print_error_complex("export", arg, "not a valid identifier");
	free(name);
	g_exit_code = 1;
	return ;
}

void	set_each_attribute(char ***env, char *arg)
{
	int		idx;
	int		len;
	char	*name;

	len = ft_strlen(arg);
	if (ft_strchr(arg, '='))
		len = ft_strchr(arg, '=') - arg;
	name = ft_substr(arg, 0, len);
	if (check_bash_var_name_convention(name) == FAILURE)
		return (handle_export_error(arg, name));
	free(name);
	idx = -1;
	while ((*env)[++idx])
	{
		if (!ft_strncmp((*env)[idx], arg, len + 1) && arg[len] == '=')
		{
			free((*env)[idx]);
			(*env)[idx] = ft_strdup(arg);
			break ;
		}
	}
	if (!(*env)[idx])
		add_env_data(env, arg);
}

void	set_export_attribute(char ***env, char **vector)
{
	int	idx;

	if (vector[1] == NULL)
	{
		print_export_attribute(*env);
		g_exit_code = 0;
		return ;
	}
	g_exit_code = 0;
	idx = 1;
	while (vector[idx])
	{
		set_each_attribute(env, vector[idx]);
		idx++;
	}
}
