/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 01:05:18 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/11 22:41:15 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void    set_export_attribute(char ***env, char *path);

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
		// path = ft_strjoin(name, path);
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

void	exec_chdir(char **targ_dir, char **prev_dir, char **curr_dir, char *path)
{
	if (chdir(*targ_dir) == SUCCESS)
	{
		*prev_dir = ft_strdup(*curr_dir);
		getcwd(*curr_dir, PATH_MAX);
	}
	else
		printf("minishell: cd: %s: %s\n", path, strerror(errno));
}

void    change_directory(char **vector, char ***env)
{
	char    *targ_dir;
	char    *prev_dir;
	char    *curr_dir;

	targ_dir = vector[1];
	prev_dir = ft_strdup(get_env(*env, "OLDPWD"));
	//printf("get_env(*env, \"OLDPWD\"): %s\n", get_env(*env, "OLDPWD"));
	curr_dir = malloc(sizeof(char) * PATH_MAX);
	getcwd(curr_dir, PATH_MAX);
	if (!vector[1])
	{
		targ_dir = get_env(*env, "HOME");
		if (!targ_dir)
		{
			//TODO: Is this an error?
			printf("minishell: cd: HOME not set");
			return ;
		}
	}
	//TODO: cd ~
	else if (!ft_strcmp(vector[1], "~"))
		targ_dir = get_env(*env, "HOME");
	else if (!ft_strcmp(vector[1], "-"))
	{
		if (!prev_dir)
		{
			printf("minishell: cd: OLDPWD not set\n");
			return ;
		}
		else
		{
			printf("%s\n", prev_dir);
			targ_dir = prev_dir;
		}
	}
	exec_chdir(&targ_dir, &prev_dir, &curr_dir, vector[1]);
	renew_env_data(env, curr_dir, prev_dir);
}

// #include <string.h>

// char** build_vector(const char* arg)
// {
// 	char** vector = malloc(3 * sizeof(char *));
// 	vector[0] = strdup("cd");
// 	vector[1] = strdup(arg);
// 	vector[2] = NULL;
// 	return vector;
// }

// void	build_env(char ***env)
// {
// 	(*env)[0] = strdup("PATH=/usr/bin");
// 	(*env)[1] = strdup("HOME=/Users/iyeonjae");
// 	(*env)[2] = NULL;
// 	return ;
// }

// void free_vector(char** vector) {
// 	free(vector[0]);
// 	free(vector[1]);
// 	free(vector);
// }

// int main(void)
// {
// 	char    *dir;
// 	char    **env;
// 	char    **vector;

// 	env = malloc(3 * sizeof(char *));
// 	build_env(&env);
// 	printf("-----------------------------------------\n");
// 	printf("cd /Users/iyeonjae/Desktop/minishell/srcs\n");
// 	vector = build_vector("/Users/iyeonjae/Desktop/minishell/srcs");
// 	change_directory(vector, &env);
// 	free_vector(vector);
// 	// printf("dir: %s\n", getcwd(dir, PATH_MAX));
// 	for (int i = 0; env[i]; i++)
// 		printf("%s\n", env[i]);
// 	printf("-----------------------------------------\n");
// 	printf("cd\n");
// 	vector = build_vector("whatever");
// 	vector[1] = NULL;
// 	change_directory(vector, &env);
// 	free_vector(vector);
// 	// printf("dir: %s\n", getcwd(dir, PATH_MAX));
// 	for (int i = 0; env[i]; i++)
// 		printf("%s\n", env[i]);
// 	printf("-----------------------------------------\n");
// 	printf("cd Desktop\n");
// 	vector = build_vector("Desktop");
// 	change_directory(vector, &env);
// 	free_vector(vector);
// 	for (int i = 0; env[i]; i++)
// 		printf("%s\n", env[i]);
// 	// printf("dir: %s\n", getcwd(dir, PATH_MAX));
// 	printf("-----------------------------------------\n");
// 	printf("cd -\n");
// 	vector = build_vector("-");
// 	change_directory(vector, &env);
// 	free_vector(vector);
// 	// printf("dir: %s\n", getcwd(dir, PATH_MAX));
// 	for (int i = 0; env[i]; i++)
// 		printf("%s\n", env[i]);
// 	printf("-----------------------------------------\n");
// 	printf("cd /\n");
// 	vector = build_vector("/");
// 	change_directory(vector, &env);
// 	free_vector(vector);
// 	// printf("dir: %s\n", getcwd(dir, PATH_MAX));
// 	for (int i = 0; env[i]; i++)
// 		printf("%s\n", env[i]);
// }
