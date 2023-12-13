/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 01:05:18 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/14 00:53:17 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

char    *get_env(char **env, char *str)
{
	int     idx;
	char    *res;

	idx = 0;
	while (env[idx])
	{
		if (!ft_strncmp(str, env[idx], ft_strlen(str)) && env[idx][ft_strlen(str)] == '=')
		{
			res = env[idx];
			break ;
		}
		idx++;
	}
	if (!env[idx])
		return (NULL);
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

void    renew_env_data(char ***env, char *curr_dir, char *prev_dir)
{
	if (prev_dir)
	{
		prev_dir = set_env_name_and_value("OLDPWD=", prev_dir);
		set_export_attribute(env, prev_dir);
		free(prev_dir);
	}
	curr_dir = set_env_name_and_value("PWD=", curr_dir);
	set_export_attribute(env, curr_dir);
	free(curr_dir);
}

int	exec_chdir(char **targ_dir, char **prev_dir, char **curr_dir, char *path)
{
	if (chdir(*targ_dir) == SUCCESS)
	{
		*prev_dir = ft_strdup(*curr_dir);
		getcwd(*curr_dir, PATH_MAX);
		g_exit_code = 0;
		return (SUCCESS);
	}
	else
	{
		printf("minishell: cd: %s: %s\n", path, strerror(errno));
		g_exit_code = 1;
		return (g_exit_code);
	}
}

void    change_directory(char **vector, char ***env)
{
	char    *targ_dir;
	char    *prev_dir;
	char    *curr_dir;

	targ_dir = vector[1];
	prev_dir = get_env(*env, "OLDPWD");
	curr_dir = malloc(sizeof(char) * PATH_MAX);
	getcwd(curr_dir, PATH_MAX);
	if (!vector[1])
	{
		targ_dir = get_env(*env, "HOME");
		if (!targ_dir)
		{
			printf("minishell: cd: HOME not set");
			free(curr_dir);
			g_exit_code = 1;
			return ;
		}
	}
	else if (!ft_strcmp(vector[1], "-"))
	{
		if (!prev_dir)
		{
			printf("minishell: cd: OLDPWD not set\n");
			free(curr_dir);
			g_exit_code = 1;
			return ;
		}
		else
		{
			printf("%s\n", prev_dir);
			targ_dir = prev_dir;
		}
	}
	if (exec_chdir(&targ_dir, &prev_dir, &curr_dir, vector[1]) == SUCCESS)
		renew_env_data(env, curr_dir, prev_dir);
	else
		free(curr_dir);
}
