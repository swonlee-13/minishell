/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 03:09:36 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/19 03:57:17 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Standard Libraries
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>
# include <signal.h>
# include <fcntl.h>
# include <termios.h>

// Readline Libraries
# include <readline/readline.h>
# include <readline/history.h>

// Custom Libraries and Definitions
# include "parse.h"
# include "../srcs/libft/libft.h"

// Macro Definitions
# define READ        0
# define WRITE       1
# define TRUE        1
# define FALSE       0
# define SUCCESS     0
# define FAILURE     -1
# define PATH_MAX    1024

// Struct Declarations
typedef struct s_file
{
	int	in;
	int	out;
	int	temp;
}	t_file;

// CD Command
void	change_directory(char **vector, char ***env);

// Echo Command
void	write_arg_to_stdout(char **vector);

// Env Command
void	print_env_list(char **env);

// Export Command
void	set_each_attribute(char ***env, char *path);
void	set_export_attribute(char ***env, char **vector);

// Pwd Command
void	print_working_directory(void);

// Unset Command
int		check_bash_var_name_convention(char *name);
void	remove_env_data(char ***env, char *name);

// Exit Command
void	terminate_program(char **vector);

// Command Execution
void	execute_command(int fd[2], int idx, t_node *root, char ***env);
void	execute_commands(t_node *tree, char ***env_copy);
pid_t	execute_pipeline(int idx, t_node *tree, t_file *redir, char ***env);

// Redirection Handling
void	setup_child_redirection(int fd[2], int idx, t_node *tree, t_file redir);
void	setup_parent_redirection(int fd[2], t_file *redir);

// Signal Handling
void	prompt_sigint_handler(int signum);
void	heredoc_sigint_handler(int signum);
void	init_signal(void);

// Here Document Utilities
void	open_files(t_node *root, char **env_copy);
void	setup_cmd_redirection(t_node *root, int cmd_idx, t_file *file);
int		activate_here_doc(t_node *node, char **env_copy);

// Builtin Command Utilities
void	execute_builtin(char **command_vector, char ***env_copy);
int		is_builtin(char *command);

// Environment Utilities
char	**copy_env_list(char **env);
char	*get_env_data(char **env, char *str);
char	*set_env_name_and_value(char *name, char *path);
void	add_env_data(char ***env, char *path);
void	renew_env_data(char ***env, char *curr_dir, char *prev_dir);

// Terminal Utilities
void	reset_termios(void);
void	set_termios(void);
void	print_error(char *cmd, char *str);
void	print_error_complex(char *cmd, char *arg, char *str);

// Command-line Utilities
char	*get_command_path(char **cmd, char **env);
int		count_commands(t_node *root);
t_node	*find_redirection_root(t_node *root, int cmd_idx);

// Others
void	setup_exit_status(pid_t pid);

#endif
