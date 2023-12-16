/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:03:24 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/17 05:09:18 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

static int	check_assignment_operator(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx])
	{
		if (str[idx] == '=')
			return (SUCCESS);
		idx++;
	}
	return (FAILURE);
}

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
		if (check_assignment_operator(res[i]) == FAILURE)
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

void	set_each_attribute(char ***env, char *path)
{
	int	idx;
	int	len;

	len = 0;
	if (check_assignment_operator(path) == SUCCESS)
		while (path[len] && path[len] != '=')
			len++;
	else
		len = ft_strlen(path);
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

void	set_export_attribute(char ***env, char **vector)
{
	int	idx;

	if (vector[1] == NULL)
	{
		print_export_attribute(*env);
		g_exit_code = 0;
		return ;
	}
	idx = 1;
	while (vector[idx])
	{
		set_each_attribute(env, vector[idx]);
		idx++;
	}
	g_exit_code = 0;
}
