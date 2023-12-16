/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_formatting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <seongwol@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 18:45:13 by seongwol          #+#    #+#             */
/*   Updated: 2023/12/16 19:21:15 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

extern int	g_exit_code;

char	*string_formatting(char *str, char **env_copy)
{
	char	**tmp;
	char	*ret;

	ret = NULL;
	tmp = shell_split_quote(str);
	remove_and_replace(tmp, env_copy);
	ret = merge_splitted_cmd(tmp);
	ft_free(tmp);
	free(str);
	return (ret);
}

void	node_data_formatting(t_queue *q, char **env_copy)
{
	t_node	*node;
	char	*tmp;

	node = q->front;
	while (node)
	{
		tmp = node->data;
		if (node->type == REDIR_DOUBLE_IN)
			node->data = limiter_formatting(tmp);
		else
			node->data = string_formatting(tmp, env_copy);
		node = node->right;
	}
}
