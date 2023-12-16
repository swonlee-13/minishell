/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 18:38:45 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/16 19:15:42 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern int	g_exit_code;

void	execute_command(int fd[2], int idx, t_node *root, char ***env)
{
	char	**vector;

	vector = vector_conversion(&root, idx);
	if (is_builtin(vector[0]))
	{
		execute_builtin(vector, env);
		exit(g_exit_code);
	}
	vector[0] = get_command_path(&vector[0], *env);
	close(fd[READ]);
	close(fd[WRITE]);
	execve(vector[0], vector, *env);
	g_exit_code = 127;
	printf("minisehll: %s: command not found\n", vector[0]);
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

void	execute_commands(t_node *tree, char ***env_copy)
{
	int			idx;
	const int	cnt = count_commands(tree);
	char		**vector;
	pid_t		last_pid;
	t_file		redir;

	idx = 0;
	while (idx < cnt)
	{
		setup_cmd_redirection(tree, idx, &redir);
		vector = vector_conversion(&tree, idx);
		if (!vector[0])
			return ;
		if (cnt == 1 && is_builtin(vector[0]))
		{
			execute_builtin(vector, env_copy);
			ft_free(vector);
			return ;
		}
		else
			last_pid = execute_pipeline(idx, tree, &redir, env_copy);
		ft_free(vector);
		idx++;
	}
	setup_exit_status(last_pid);
}
