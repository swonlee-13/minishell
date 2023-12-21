/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:32:11 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/21 20:04:44 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code = 0;

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

void	execute_and_cleanup(t_node **tree, char ***env)
{
	if (g_exit_code != 260)
	{
		open_files(*tree, *env);
		if (g_exit_code != 259)
			execute_commands(*tree, env);
		else
			g_exit_code = 1;
	}
	else
		g_exit_code = 258;
}

int	main(int argc, char *argv[], char **env)
{
	char	**env_copy;
	char	*cmd_line;
	t_node	*tree;

	env_copy = copy_env_list(env);
	while (argc || argv)
	{
		set_termios();
		init_signal();
		cmd_line = readline("minishell> ");
		if (!cmd_line)
			break ;
		if (ft_strcmp(cmd_line, "") != 0)
			add_history(cmd_line);
		tree = parser(cmd_line, env_copy);
		free(cmd_line);
		execute_and_cleanup(&tree, &env_copy);
		free_tree(tree);
	}
	printf("\x1b[1A\033[11Cexit\n");
	reset_termios();
	return (SUCCESS);
}
