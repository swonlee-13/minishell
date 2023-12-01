/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_find_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 21:32:27 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/01 21:32:36 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*find_redirection_root(t_node *root, int cmd_idx)
{
	t_node	*ptr;
	int		idx;

	ptr = root;
	idx = 1;
	while (idx < cmd_idx)
	{
		ptr = ptr->right;
		idx++;
	}
	ptr = ptr->left->left;
	return (ptr);
}

