/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 19:22:18 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/11 22:39:07 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_node	*get_command_tree(t_node *root, int idx)
{
	t_node	*ptr;

	ptr = root;
	while (idx--)
		ptr = ptr->right;
	return (ptr);
}

t_node	*node_init_with_vars(t_type type, int cmd_idx)
{
	t_node	*new;

	new = node_init();
	new->type = type;
	new->pipe_index = cmd_idx;
	return (new);
}

void	sub_tree_insert(t_node **root, int cmd_idx)
{
	t_node	*node;

	node = node_init_with_vars(PIPE, cmd_idx);
	tree_insert_pipe(root, node);
	node = node_init_with_vars(CMD, cmd_idx);
	tree_insert(root, node);
	node = node_init_with_vars(REDIRECTION_ROOT, cmd_idx);
	tree_insert(root, node);
	node = node_init_with_vars(ARGUMENT_ROOT, cmd_idx);
	tree_insert(root, node);
}

void	tree_insert_redir(t_node **root, t_node *tmp, int cmd_idx)
{
	t_node	*ptr;
	t_node	*node;
	int		i;

	ptr = *root;
	i = 0;
	while (++i < cmd_idx)
	{
		ptr = ptr->right;
		i++;
	}
	ptr = ptr->left->left;
	while (ptr->right)
		ptr = ptr->right;
	node = node_init_with_vars(REDIRECTION_ROOT, cmd_idx);
	ptr->right = node;
	ptr->right->left = tmp;
}

t_node	*switch_to_tree(t_queue *q)
{
	t_node	*root;
	t_node	*tmp;

	if (q == NULL)
		return (NULL);
	root = NULL;
	tmp = dequeue(q);
	sub_tree_insert(&root, tmp->pipe_index);
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			sub_tree_insert(&root, tmp->pipe_index + 1);
			free(tmp->data);
			free(tmp);
		}
		else if ((int)tmp->type > 0 && (int)tmp->type < 5)
			tree_insert_redir(&root, tmp, tmp->pipe_index + 1);
		else
			tree_insert(&root, tmp);
		tmp = dequeue(q);
	}
	return (root);
}
