/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 18:38:45 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/23 18:45:51 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern int	g_exit_code;

void	execute_command(int fd[2], int idx, t_node *root, char ***env)
{
	char	**vector;

	vector = vector_conversion(&root, idx);
	if (vector[0] == NULL)
		exit(g_exit_code);
	if (is_builtin(vector[0]))
	{
		execute_builtin(vector, env);
		exit(g_exit_code);
	}
	vector[0] = get_command_path(&vector[0], *env);
	close(fd[READ]);
	close(fd[WRITE]);
	g_exit_code = execve(vector[0], vector, *env);
}

pid_t	execute_pipeline(int idx, t_node *tree, t_file *redir, char ***env)
{
	pid_t	pid;
	int		fd[2];

	signal(SIGINT, SIG_IGN);
	pipe(fd);
	pid = fork();
	if (pid < 0)
		printf("minishell: %s\n", strerror(errno));
	if (pid == 0)
	{
		reset_termios();
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		setup_child_redirection(fd, idx, tree, *redir);
		if (redir->in != -1 && redir->out != -1)
			execute_command(fd, idx, tree, env);
		exit(g_exit_code);
	}
	else
	{
		if (idx > 0)
			close(redir->temp);
		setup_parent_redirection(fd, redir);
	}
	return (pid);
}

int	single_command_redirection(t_file *file)
{
	if (file->in != STDIN_FILENO)
	{
		dup2(file->in, STDIN_FILENO);
		close(file->in);
	}
	if (file->out != STDOUT_FILENO)
	{
		dup2(file->out, STDOUT_FILENO);
		close(file->out);
	}
	return (TRUE);
}

void	execute_single_command(t_node *tree, t_file *file, char ***env_copy)
{
	char	**commands;
	int		my_stdin;
	int		my_stdout;

	my_stdin = dup(STDIN_FILENO);
	my_stdout = dup(STDOUT_FILENO);
	if (file->in == -1 || file->out == -1)
	{
		if (file->out == -1 && file->in != STDIN_FILENO)
			close(file->in);
		if (file->in == -1 && file->out != STDOUT_FILENO)
			close(file->out);
		g_exit_code = 255;
		return ;
	}
	single_command_redirection(file);
	commands = vector_conversion(&tree, 0);
	execute_builtin(commands, env_copy);
	dup2(my_stdin, STDIN_FILENO);
	dup2(my_stdout, STDOUT_FILENO);
	close(my_stdin);
	close(my_stdout);
	ft_free(commands);
	return ;
}

void	execute_commands(t_node *tree, char ***env_copy)
{
	int			idx;
	const int	cnt = count_commands(tree);
	pid_t		last_pid;
	t_file		redir;

	idx = -1;
	while (++idx < cnt)
	{
		redir.in = STDIN_FILENO;
		redir.out = STDOUT_FILENO;
		setup_cmd_redirection(tree, idx, &redir);
		if (cnt == 1 && tree->left->right->right && \
			is_builtin(tree->left->right->right->data))
		{
			execute_single_command(tree, &redir, env_copy);
			return ;
		}
		else
			last_pid = execute_pipeline(idx, tree, &redir, env_copy);
	}
	if (cnt != 0)
		setup_exit_status(last_pid);
}
