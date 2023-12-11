/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_redirection_root.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 21:32:27 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/12 02:35:27 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_node	*find_redirection_root(t_node *root, int cmd_idx)
{
	t_node	*ptr;
	int		idx;

	ptr = root;
	idx = 0;
	while (idx < cmd_idx)
	{
		ptr = ptr->right;
		idx++;
	}
	ptr = ptr->left->left;
	return (ptr);
}

