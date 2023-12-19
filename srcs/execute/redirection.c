/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 18:37:13 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/19 00:07:28 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern int	g_exit_code;

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

void	open_files(t_node *root, char **env_copy)
{
	if (root == NULL)
		return ;
	if (root->type == REDIR_DOUBLE_IN)
		activate_here_doc(root, env_copy);
	else if (root->type == REDIR_SINGLE_IN)
		root->fd = open(root->data, O_RDONLY, 0644);
	else if (root->type == REDIR_SINGLE_OUT)
		root->fd = open(root->data, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (root->type == REDIR_DOUBLE_OUT)
		root->fd = open(root->data, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (root->fd == -1)
	{
		g_exit_code = 1;
		print_no_file_error(root->data);
		return ;
	}
	open_files(root->left, env_copy);
	open_files(root->right, env_copy);
}
