/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:32:11 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/16 18:54:24 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code = 0;

char	*get_command_path(char **cmd, char **env)
{
	int		idx;
	char	*tmp1;
	char	*tmp2;
	char	**path;

	if (cmd[0][0] == '/' || \
		(cmd[0][0] == '.' && cmd[0][1] == '/'))
		if (!access(*cmd, X_OK))
			return (*cmd);
	path = ft_split(get_env_data(env, "PATH"), ':');
	tmp1 = ft_strjoin("/", *cmd);
	idx = -1;
	while (path[++idx])
	{
		tmp2 = ft_strjoin(path[idx], tmp1);
		if (!access(tmp2, X_OK))
		{
			free(tmp1);
			ft_free(path);
			return (tmp2);
		}
		free(tmp2);
	}
	free(tmp1);
	return (*cmd);
}

void	setup_exit_status(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (status == SIGINT)
		ft_putstr_fd("\n", STDERR_FILENO);
	else if (status == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
	if (WIFEXITED(status))
		g_exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_code = 128 + WTERMSIG(status);
	while (waitpid(0, &status, 0) >= 0)
	{
		if (WIFSIGNALED(status))
			if (WTERMSIG(status) == SIGINT)
				ft_putstr_fd("\n", STDERR_FILENO);
		while (waitpid(0, NULL, 0) >= 0)
			;
	}
}

void	execute_and_cleanup(t_node *tree, char **env)
{
	if (g_exit_code != 258)
	{
		g_exit_code = 0;
		open_files(tree, env);
		if (g_exit_code != 1)
			execute_commands(tree, &env);
	}
	free_tree(tree);
}

int	main(int argc, char *argv[], char **env)
{
	char			**env_copy;
	char			*cmd_line;
	t_node			*tree;

	env_copy = copy_env_list(env);
	while (argc || argv)
	{
		set_termios();
		init_signal();
		cmd_line = readline("minishell> ");
		if (!cmd_line)
			break ;
		add_history(cmd_line);
		tree = parser(cmd_line, env_copy);
		free(cmd_line);
		execute_and_cleanup(tree, env_copy);
	}
	printf("\x1b[1A\033[11Cexit\n");
	reset_termios();
	return (SUCCESS);
}
