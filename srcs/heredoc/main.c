/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:32:11 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/02 04:44:01 by yeolee2          ###   ########.fr       */
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

	ptr = root;
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
		print_working_directory();
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

t_file	setup_cmd_redirection(int idx, t_node *parsed_commands)
{
	t_node	*temp;
	t_file	fd = { .in = STDIN_FILENO, .out = STDOUT_FILENO };

	temp = find_redirection_root(parsed_commands, idx);
	while (temp)
	{
		if (temp->type == REDIR_DOUBLE_IN)
		{
			fd.in = temp->fd;
			dup2(fd.in, STDIN_FILENO);
			close(fd.in);
		}
		else if (temp->type == REDIR_SINGLE_IN)
		{
			fd.in = open(temp->data, O_RDONLY);
			dup2(fd.in, STDIN_FILENO);
			close(fd.in);
		}
		else if (temp->type == REDIR_DOUBLE_OUT)
		{
			fd.out = open(temp->data, O_RDWR | O_CREAT | O_APPEND, 0644);
			dup2(fd.out, STDOUT_FILENO);
			close(fd.out);
		}
		else if (temp->type == REDIR_SINGLE_OUT)
		{
			fd.out = open(temp->data, O_RDWR | O_CREAT | O_TRUNC, 0644);
			dup2(fd.out, STDOUT_FILENO);
			close(fd.out);
		}
		temp = temp->left;
	}
	return (fd);
}

void	setup_parent_redirection(t_file redir, int fd[2])
{
	//FIXME: Parent redirection needs to be revised
	dup2(fd[READ], STDIN_FILENO);
	close(fd[READ]);
	close(fd[WRITE]);
}

void    execute_pipeline(int idx, t_node *parsed_commands, char ***env_copy)
{
	t_file	redir;
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	pid = fork();
	if (pid < 0)
	{
        printf("%s\n", strerror(errno));
		return ;
	}
	// Child process
	if (pid == 0)
	{
		// Setup command-specific redirections
		redir = setup_cmd_redirection(idx, parsed_commands);
		if (idx > 0)
			// If this is not the first command in the pipeline,
            // use the read end of the previous command's pipe as standard input
			dup2(fd[READ], STDIN_FILENO);
		else
			// If this is the first command in the pipeline,
            // use the standard input redirection specified by the command itself
			dup2(redir.in, STDIN_FILENO);
		if (idx < count_commands(parsed_commands) - 1)
			// If this is not the last command in the pipeline,
            // use the write end of the current command's pipe as standard output
			dup2(fd[WRITE], STDOUT_FILENO);
		else
			// If this is the last command in the pipeline,
            // use the standard output redirection specified by the command itself
			dup2(redir.out, STDOUT_FILENO);
		execute_command(fd, idx, parsed_commands, env_copy);
		exit(0);
		// setup_redirections();
	}
	else
		setup_parent_redirection(redir, fd);
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
		command_vector = vector_conversion(&parsed_commands, idx);
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

	(void)argc;
	(void)argv;
	env_copy = copy_env_list(env);
	while (TRUE)
	{
		// init_sig()
		init_sig();
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
