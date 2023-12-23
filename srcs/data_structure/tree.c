/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <seongwol@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 19:55:23 by seongwol          #+#    #+#             */
/*   Updated: 2023/12/23 20:59:15 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	tree_action(t_node **ptr, t_node *target)
{
	if (*ptr == NULL)
	{
		*ptr = target;
		return ;
	}
	if (target->type < (*ptr)->type)
		tree_action(&(*ptr)->left, target);
	else
		tree_action(&(*ptr)->right, target);
}

void	tree_insert_pipe(t_node **root, t_node *target)
{
	t_node	*ptr;
	int		i;

	if (*root == NULL)
	{
		*root = target;
		return ;
	}
	ptr = *root;
	i = -1;
	while (++i < target->pipe_index - 1)
		ptr = ptr->right;
	ptr->right = target;
}

void	tree_insert(t_node **root, t_node *target)
{
	t_node	*ptr;
	int		i;

	if (*root == NULL)
	{
		*root = target;
		return ;
	}
	ptr = *root;
	i = -1;
	while (++i < target->pipe_index)
		ptr = ptr->right;
	tree_action(&ptr, target);
}

void	free_tree(t_node *root)
{
	if (root == NULL)
		return ;
	free_tree(root->left);
	free_tree(root->right);
	free(root->data);
	free(root);
}

void	target_init(t_node **target, int type)
{
	*target = (t_node *)malloc(sizeof(t_node));
	(*target)->left = NULL;
	(*target)->right = NULL;
	(*target)->type = type;
}
