/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <seongwol@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 19:56:08 by seongwol          #+#    #+#             */
/*   Updated: 2023/12/18 17:28:11 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

char	*create_here_doc_file(t_node *node)
{
	char		*file_name;
	static int	number;
	char		*numstr;

	number++;
	numstr = ft_itoa(number);
	file_name = ft_strjoin("/tmp/my_here_doc", numstr);
	while (access(file_name, F_OK) == SUCCESS)
	{
		free(file_name);
		free(numstr);
		number++;
		numstr = ft_itoa(number);
		file_name = ft_strjoin("/tmp/my_here_doc", numstr);
	}
	node->fd = open(file_name, O_RDWR | O_CREAT | O_EXCL | O_TRUNC, 0644);
	free(numstr);
	return (file_name);
}

void	write_here_doc(t_node *node, char **env_copy)
{
	char	*buffer;

	while (1)
	{
		buffer = readline("> ");
		if (buffer == 0 || ft_strcmp(buffer, node->data) == 0)
			break ;
		buffer = here_doc_formatting(buffer, env_copy);
		ft_putstr_fd(buffer, node->fd);
		ft_putstr_fd("\n", node->fd);
		free(buffer);
	}
	free(buffer);
}

int	activate_here_doc(t_node *node, char **env_copy)
{
	int		fd;
	char	*file_name;

	fd = dup(STDIN_FILENO);
	signal(SIGINT, heredoc_sigint_handler);
	file_name = create_here_doc_file(node);
	write_here_doc(node, env_copy);
	dup2(fd, STDIN_FILENO);
	close(fd);
	close(node->fd);
	node->fd = open(file_name, O_RDONLY);
	unlink(file_name);
	signal(SIGINT, prompt_sigint_handler);
	free(file_name);
	return (SUCCESS);
}

void	setup_cmd_redirection(t_node *root, int cmd_idx, t_file *file)
{
	t_node	*ptr;

	ptr = find_redirection_root(root, cmd_idx);
	ptr = ptr->right;
	while (ptr && file->in != -1 && file->out != -1)
	{
		if (ptr->left->type == REDIR_DOUBLE_IN \
		|| ptr->left->type == REDIR_SINGLE_IN)
		{
			if (file->in != STDIN_FILENO)
				close(file->in);
			file->in = ptr->left->fd;
		}
		else if (ptr->left->type == REDIR_SINGLE_OUT \
		|| ptr->left->type == REDIR_DOUBLE_OUT)
		{
			if (file->out != STDOUT_FILENO)
				close(file->out);
			file->out = ptr->left->fd;
		}
		ptr = ptr->right;
	}
}
