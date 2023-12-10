/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 03:09:36 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/10 00:37:14 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>
# include <signal.h>
# include <fcntl.h>
# include <termios.h>
# include <readline/readline.h>
# include "../srcs/libft/libft.h"
# define READ       0
# define WRITE      1
# define TRUE       1
# define FALSE      0
# define SUCCESS    0
# define FAILURE    -1
# define PATH_MAX   1024

typedef struct s_file
{
    int in;
    int out;
	int	temp;
}       t_file;

/* UTILS */
char	**copy_env_list(char **env);
char	*find_env_data(char **env, char *str);
void    init_sig();

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
int     check_bash_var_name_convention(char *name);
void	remove_env_data(char ***env, char *name);

/* SIGNAL */
void    child_sigint_handler(int signum);
void    parent_sigint_handler(int signum);
void    sig_pa(int signo);
#endif
