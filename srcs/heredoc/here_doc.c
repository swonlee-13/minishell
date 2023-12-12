/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <seongwol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:30:57 by seongwol          #+#    #+#             */
/*   Updated: 2023/12/12 02:30:44 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		// write(1, "heredoc> ", 9);
		buffer = readline("> ");
		if (buffer == 0 || ft_strcmp(buffer, node->data) == 0)
			break;
		buffer = here_doc_formatting(buffer, env_copy);
		ft_putstr_fd(buffer, node->fd);
		ft_putstr_fd("\n", node->fd);
		free(buffer);
	}
	free(buffer);
	// free(end);
}

int	activate_here_doc(t_node *node, char **env_copy)
{
	char	*file_name;

	file_name = create_here_doc_file(node);
//	if (node->fd == -1)
//	{
//		perror(errno); //TODO: 에러 관련 처리 합시다
//		return(errno); //TODO: 에러 관련 처리 합시다
//	}
	write_here_doc(node, env_copy);
	close(node->fd);
	node->fd = open(file_name, O_RDONLY);
//	if (node->fd == -1)
//	{
//		perror(errno); //TODO: 에러 관련 처리 합시다
//		return(errno); //TODO: 에러 관련 처리 합시다
//	}
	unlink(file_name);
	free(file_name);
	return (SUCCESS);
}

void	open_files(t_node *root, char **env_copy)
{
	if (root == NULL)
		return ;
	if (root->type == REDIR_DOUBLE_IN)
		activate_here_doc(root, env_copy);
	else if (root->type == REDIR_SINGLE_IN)
		root->fd = open(root->data, O_RDONLY);
	else if (root->type == REDIR_SINGLE_OUT)
		root->fd = open(root->data, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (root->type == REDIR_DOUBLE_OUT)
		root->fd = open(root->data, O_RDWR | O_CREAT | O_APPEND, 0644);
	open_files(root->left, env_copy);
	open_files(root->right, env_copy);
}

void	setup_cmd_redirection(t_node *root, int cmd_idx, t_file *file)
{
	t_node	*ptr;

	file->in = STDIN_FILENO;
	file->out = STDOUT_FILENO;
	ptr = find_redirection_root(root, cmd_idx);
	ptr = ptr->right;
	while (ptr)
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
