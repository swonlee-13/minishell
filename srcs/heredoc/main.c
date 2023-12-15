/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:32:11 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/15 04:15:26 by yeolee2          ###   ########.fr       */
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

void	setup_child_redirection(int fd[2], int idx, t_node *tree, t_file redir)
{
	if (idx > 0 && redir.in == STDIN_FILENO)
	{
		dup2(redir.temp, STDIN_FILENO);
		close(redir.temp);
	}
	if (idx < count_commands(tree) - 1 && redir.out == STDOUT_FILENO)
		dup2(fd[WRITE], STDOUT_FILENO);
	if (redir.in != STDIN_FILENO)
		dup2(redir.in, STDIN_FILENO);
	if (redir.out != STDOUT_FILENO)
		dup2(redir.out, STDOUT_FILENO);
}

void	setup_parent_redirection(int fd[2], t_file *redir)
{
	if (redir->in != STDIN_FILENO)
		close(redir->in);
	redir->temp = dup(fd[READ]);
	if (redir->out != STDOUT_FILENO)
		close(redir->out);
	close(fd[READ]);
	close(fd[WRITE]);
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
}

void    execute_commands(t_node *tree, char ***env_copy)
{
	int			idx;
	const int   cnt = count_commands(tree);
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
	int	status;
	while (waitpid(0, &status, 0) >= 0)
	{
		if (WIFSIGNALED(status))
			if (WTERMSIG(status) == SIGINT)
				ft_putstr_fd("\n", STDERR_FILENO);
		while (waitpid(0, NULL, 0) >= 0)
			;
	}
}

void	reset_termios(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, 0, &term);
}

void	set_termios(void)
{
	struct termios	term;
	
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, 0, &term);
}

int main(int argc, char *argv[], char **env)
{
	char			*command_line;
	char			**env_copy;
	t_node			*parsed_commands;
	(void)argc;
	(void)argv;
	g_exit_code = 0;
	env_copy = copy_env_list(env);
	while (TRUE)
	{
		set_termios();
		init_signal();
		command_line = readline("minishell> ");
		if (!command_line)
			break ;
		add_history(command_line);
		parsed_commands = parser(command_line, env_copy);
		if (g_exit_code != 258)
		{
			g_exit_code = 0;
			open_files(parsed_commands, env_copy);
			if (g_exit_code != 1)
				execute_commands(parsed_commands, &env_copy);
		}
		free_tree(parsed_commands);
		free(command_line);
	}
	printf("\x1b[1A\033[11Cexit\n");
	reset_termios();
	return (SUCCESS);
}
