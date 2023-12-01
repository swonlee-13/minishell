/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:32:11 by yeolee2           #+#    #+#             */
/*   Updated: 2023/11/30 02:31:51 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int count_commands(t_node *root)
{
	t_node  *ptr;
	int     cnt;

	ptr = root;
	cnt	= 0;
	while (ptr)
	{
		ptr = ptr->right;
		cnt++;
	}
	return (cnt);
}

t_node	*get_command_tree(t_node *root, int idx)
{
	t_node	*ptr;

	while (idx--)
		ptr = ptr->right;
	return (ptr);
}

void    execute_builtin(char **command_vector, char ***env_copy)
{
	if (!ft_strcmp(command_vector[0], "cd"))
		change_directory(command_vector, env_copy);
	else if (!ft_strcmp(command_vector[0], "echo"))
		write_arg_to_stdout(command_vector);
	else if (!ft_strcmp(command_vector[0], "env"))
		print_env_list(*env_copy);
	else if (!ft_strcmp(command_vector[0], "exit"))
	{
		//TODO: 
	}
	else if (!ft_strcmp(command_vector[0], "export"))
		set_export_attribute(env_copy, command_vector[1]);
	else if (!ft_strcmp(command_vector[0], "pwd"))
		print_working_directory;
	else if (!ft_strcmp(command_vector[0], "unset"))
		remove_env_data(env_copy, command_vector[1]);
}

int is_builtin(char *command)
{
	if (!ft_strcmp(command, "cd"))
		return (TRUE);
	if (!ft_strcmp(command, "echo"))
		return (TRUE);
	if (!ft_strcmp(command, "env"))
		return (TRUE);
	if (!ft_strcmp(command, "exit"))
		return (TRUE);
	if (!ft_strcmp(command, "export"))
		return (TRUE);
	if (!ft_strcmp(command, "pwd"))
		return (TRUE);
	if (!ft_strcmp(command, "unset"))
		return (TRUE);
	return (FALSE);
}

// void	setup_redirections(t_node *root, int fd[2])
// {
// 	t_node	*curr;
// 	int	idx;

// 	idx = 0;
// 	curr = root;
// 	while (curr->left)
// 	{
// 		if (curr->left)
// 		{
// 			/* code */
// 		}
		
// 		curr = curr->left;
// 	}
	
// }

void	execute_command(int fd[2], int idx, t_node *root, char ***env_copy)
{
	char	**command_vector;

	command_vector = vector_conversion(&root, idx);
	close(fd[READ]);
	close(fd[WRITE]);
	execve(command_vector[0], command_vector, *env_copy);
	//TODO: Error handling in case of execve failure
	//TODO: Return value needs to be discussed
	// exit(EXIT_FAILURE);
}

void	setup_child_redirection(t_file file, int fd[2], int idx, t_node *root)
{
	if (dup2(file.in, STDIN_FILENO) == FAILURE)
			printf("%s\n", strerror(errno));
	if (idx == count_commands(root) - 1)
	{
		//TODO: How to setup redirections when outfile doesn't exist in the last pipeline
		if (dup2(file.out, STDOUT_FILENO) == FAILURE)
			printf("%s\n", strerror(errno));	
	}
	else
	{
		if (dup2(fd[WRITE], STDOUT_FILENO))
			printf("%s\n", strerror(errno));
	}
}

void	setup_parent_redirection(int infile, int fd[2])
{
	dup2(fd[READ], infile);
	close(fd[READ]);
	close(fd[WRITE]);
}

void    execute_pipeline(int idx, t_node *root, char ***env_copy)
{
	pid_t	pid;
	t_file	file;
	int		fd[2];
	int     tmp;

	//TODO: Open file in accordance
	pipe(fd);
	pid = fork();
	if (pid < 0)
	{
        printf("%s\n", strerror(errno));
		return ;
	}
	if (pid == 0)
	{
		// Child process
		setup_child_redirection(file, fd, idx, root);
		execute_command(fd, idx, root, env_copy);
		exit(0);
		// setup_redirections();
	}
	else
		setup_parent_redirection(file.in, fd);
	while (waitpid(0, NULL, 0) >= 0)
		;
}

void    execute_commands(t_node *parsed_commands, char ***env_copy)
{
	int			idx;
	const int   cnt = count_commands(parsed_commands);
	char		**command_vector;

	idx = 0;
	while (idx < cnt)
	{
		command_vector = vector_conversion(parsed_commands, idx);
		if (cnt == 1 && is_builtin(command_vector[0]))
			execute_builtin(command_vector, env_copy);
		else
			execute_pipeline(idx, parsed_commands, env_copy);
		ft_free(command_vector);
		idx++;
	}
}

int main(int argc, char *argv[], char **env)
{
	char    *command_line;
	char    **env_copy;
	t_node  *parsed_commands;

	env_copy = copy_env_list(env);
	while (TRUE)
	{
		command_line = readline("minishell> ");
		// if (/* !ft_strcmp(command_line, SIGNAL)*/ || !ft_strcmp(command_line, "exit"))
		// {
		//     //TODO: Signal handling
		//     break ;
		// }
		parsed_commands = parser(command_line, env_copy);
		//TODO: setup_heredoc();
		execute_commands(parsed_commands, &env_copy);
		free_tree(parsed_commands);
		free(command_line);
	}
}
