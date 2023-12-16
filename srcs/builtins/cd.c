/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 01:05:18 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/15 19:49:41 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

static int	exec_chdir(char **targ_dir, char **prev_dir, \
	char **curr_dir, char *path)
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

static void	handle_cd_error(char *targ_dir, char *curr_dir)
{
	printf("minishell: cd: %s not set\n", targ_dir);
	free(curr_dir);
	g_exit_code = 1;
	return ;
}

void	change_directory(char **vector, char ***env)
{
	char	*targ_dir;
	char	*prev_dir;
	char	*curr_dir;

	targ_dir = vector[1];
	prev_dir = get_env_data(*env, "OLDPWD");
	curr_dir = malloc(sizeof(char) * PATH_MAX);
	getcwd(curr_dir, PATH_MAX);
	if (!vector[1])
	{
		targ_dir = get_env_data(*env, "HOME");
		if (!targ_dir)
			return (handle_cd_error("HOME", curr_dir));
	}
	else if (!ft_strcmp(vector[1], "-"))
	{
		if (!prev_dir)
			return (handle_cd_error("OLDPWD", curr_dir));
		printf("%s\n", prev_dir);
		targ_dir = prev_dir;
	}
	if (exec_chdir(&targ_dir, &prev_dir, &curr_dir, vector[1]) == SUCCESS)
		renew_env_data(env, curr_dir, prev_dir);
	else
		free(curr_dir);
}
