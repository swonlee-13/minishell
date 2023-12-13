/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:32:11 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/13 15:21:19 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code = 0;

char	*get_command_path(char **command, char **env_copy)
{
	int		idx;
	char	*temp;
	char	**path;

	path = ft_split(get_env(env_copy, "PATH"), ':');
	temp = ft_strjoin("/", *command);
	free(*command);
	idx = -1;
	while (path[++idx])
	{
		*command = ft_strjoin(path[idx], temp);
		if (!access(*command, X_OK))
		{
			free(temp);
			ft_free(path);
			return (*command);
		}
		else
			free(*command);
	}
	return (NULL);
}

void	execute_command(int fd[2], int idx, t_node *root, char ***env_copy)
{
	char	**command_vector;

	command_vector = vector_conversion(&root, idx);
	if (is_builtin(command_vector[0]))
		execute_builtin(command_vector, env_copy);
	command_vector[0] = get_command_path(&command_vector[0], *env_copy);
	close(fd[READ]);
	close(fd[WRITE]);
	execve(command_vector[0], command_vector, *env_copy);
	//TODO: Error handling in case of execve failure
	//TODO: Return value needs to be discussed
	// exit(EXIT_FAILURE);
}

void	setup_child_redirection(int fd[2], int idx, t_node *parsed_commands, t_file redir)
{
	if (idx > 0 && redir.in == STDIN_FILENO)
	{
		dup2(redir.temp, STDIN_FILENO);
		close(redir.temp);
	}
	if (idx < count_commands(parsed_commands) - 1 && redir.out == STDOUT_FILENO)
		dup2(fd[WRITE], STDOUT_FILENO);
	if (redir.in != STDIN_FILENO)
		dup2(redir.in, STDIN_FILENO);
	if (redir.out != STDOUT_FILENO)
		dup2(redir.out, STDOUT_FILENO);
}

void	setup_parent_redirection(int fd[2], t_file *redir)
{
	//FIXME: Parent redirection needs to be revised
	if (redir->in != STDIN_FILENO)
		close(redir->in);
	redir->temp = dup(fd[READ]);
	if (redir->out != STDOUT_FILENO)
		close(redir->out);
	close(fd[READ]);
	close(fd[WRITE]);
}

pid_t	execute_pipeline(int idx, t_node *parsed_commands, t_file *redir, char ***env_copy)
{
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	pid = fork();
	if (pid < 0)
	{
		//TODO: Fork error
        printf("%s\n", strerror(errno));
		// return ;
	}
	// Child process
	if (pid == 0)
	{
		// signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		reset_termios();
		// Setup command-specific redirections
		setup_child_redirection(fd, idx, parsed_commands, *redir);
		execute_command(fd, idx, parsed_commands, env_copy);
		exit(EXIT_FAILURE);
	}
	else
		setup_parent_redirection(fd, redir);
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
	if (WIFSIGNALED(status))
		g_exit_code = 128 + WTERMSIG(status);
	else
		g_exit_code = WEXITSTATUS(status);
}

void    execute_commands(t_node *parsed_commands, char ***env_copy)
{
	int			idx;
	const int   cnt = count_commands(parsed_commands);
	char		**command_vector;
	pid_t		last_pid;
	t_file		redir;

	idx = 0;
	while (idx < cnt)
	{
		setup_cmd_redirection(parsed_commands, idx, &redir);
		command_vector = vector_conversion(&parsed_commands, idx);
		if (!command_vector[0])
			return ;
		if (cnt == 1 && is_builtin(command_vector[0]))
			execute_builtin(command_vector, env_copy);
		else
			last_pid = execute_pipeline(idx, parsed_commands, &redir, env_copy);
		ft_free(command_vector);
		idx++;
	}
	setup_exit_status(last_pid);
	while (waitpid(0, NULL, 0) >= 0)
		;
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
	//TODO: May not be necessary to initialize g_exit_code
	g_exit_code = 0;
	env_copy = copy_env_list(env);
	//TODO: Save copy of argv[0] in SHELL path
	while (TRUE)
	{
		set_termios();
		init_signal();
		command_line = readline("minishell> ");
		// Handle SIGTERM
		if (!command_line)
			break ;
		add_history(command_line);
		parsed_commands = parser(command_line, env_copy);
		//TODO: setup_heredoc();
		open_files(parsed_commands, env_copy);
		execute_commands(parsed_commands, &env_copy);
		free_tree(parsed_commands);
		free(command_line);
	}
	printf("\x1b[1A\033[11Cexit\n");
	reset_termios();
	return (SUCCESS);
}
