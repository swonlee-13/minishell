/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:30:57 by seongwol          #+#    #+#             */
/*   Updated: 2023/12/08 20:58:37 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"
char	*create_here_doc_file(t_node *node)
{
	char		*file_name;
	static int	number;

	number++;
	file_name = ft_strjoin("/tmp/my_here_doc", ft_itoa(number));
	while (access(file_name, F_OK) != SUCCESS)
	{
		free(file_name);
		number++;
		file_name = ft_strjoin("/tmp/my_here_doc", ft_itoa(number));
	}
	node->fd = open(file_name, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC);
	return (file_name);
}

void	write_here_doc(t_node *node, char **env_copy)
{
	char	*end;
	char	*buffer;

	end = ft_strjoin(node->data, "\n");
	while (1)
	{
		write(1, "heredoc> ", 9);
		buffer = get_next_line(STDIN_FILENO);
		if (*buffer == 0 || ft_strcmp(buffer, end) == 0)
			break;
		buffer = here_doc_formatting(buffer, env_copy);
		ft_putstr_fd(buffer, node->fd);
		free(buffer);
	}
	free(buffer);
	free(end);
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
	ptr = ptr->left;
	while (ptr)
	{
//		if (ptr->fd == -1) //TODO: error handling needed.
//			return (error);
		if (ptr->type == REDIR_DOUBLE_IN || ptr->type == REDIR_SINGLE_IN)
		{
			if (file->in != STDIN_FILENO)
				close(file->in);
			file->in = ptr->fd;
		}
		else if (ptr->type == REDIR_SINGLE_OUT || ptr->type == REDIR_DOUBLE_OUT)
		{
			if (file->out != STDOUT_FILENO)
				close(file->out);
			file->out = ptr->fd;
		}
		ptr = ptr->left;
	}
}
