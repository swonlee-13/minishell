/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 03:09:36 by yeolee2           #+#    #+#             */
/*   Updated: 2023/11/28 14:45:44 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "../srcs/libft/libft.h"
# include "parse.h"
# define TRUE       1
# define FALSE      0
# define SUCCESS    0
# define FAILURE    -1
# define PATH_MAX   1024

/* UTILS */
char	**copy_env(char **env);
char	*find_env_data(char **env, char *str);

/* CD.C */
char    *get_env(char **env, char *str);
char	*set_env_name_and_value(char *name, char *path);
void    renew_env_data(char ***env, char *curr_dir, char *prev_dir);
void	exec_chdir(char **targ_dir, char **prev_dir, char **curr_dir, char *path);
void    change_directory(char **vector, char ***env);

/* ECHO.C */
int     check_the_rest_of_arg(char *arg);
int     is_n_option(char *arg);
void    write_arg_to_stdout(char **vector);

/* ENV.C */
void    print_env_list(char **env);

/* EXPORT.C */
void	add_env_data(char ***env, char *path);
void    set_export_attribute(char ***env, char *path);

/* PWD.C */
void    print_working_directory(void);

/* UNSET.C */
int	check_bash_var_name_convention(char *name);
void	remove_env_data(char ***env, char *name);

#endif
