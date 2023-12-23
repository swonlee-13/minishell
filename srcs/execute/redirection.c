/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 18:37:13 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/23 20:39:24 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	open_files_sub(t_node *root, char **env_copy, int *err_flag)
{
	if (g_exit_code == 259 || *err_flag != 0)
		return ;
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
		print_error(root->data, strerror(errno));
		*err_flag = 1;
		return ;
	}
	open_files_sub(root->left, env_copy, err_flag);
	open_files_sub(root->right, env_copy, err_flag);
}

void	open_files(t_node *root, char **env_copy)
{
	t_node 	*ptr;
	int		err_flag;

	ptr = root;
	while (ptr)
	{
		err_flag = 0;
		open_files_sub(ptr->left, env_copy, &err_flag);
		ptr = ptr->right;
	}
}

