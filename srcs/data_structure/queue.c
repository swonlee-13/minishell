/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <seongwol@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 19:52:35 by seongwol          #+#    #+#             */
/*   Updated: 2023/12/16 19:55:31 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	queue_is_empty(t_queue *q)
{
	if (q->node_count == 0)
		return (1);
	else
		return (0);
}

void	node_enqueue(t_queue *q, t_node *new)
{
	if (queue_is_empty(q))
		q->front = new;
	else
		q->rear->right = new;
	q->rear = new;
	q->node_count++;
	new->pipe_index = q->total_cmd_num;
}

t_node	*dequeue(t_queue *q)
{
	t_node	*ptr;

	if (queue_is_empty(q))
		return (NULL);
	ptr = q->front;
	q->front = q->front->right;
	q->node_count--;
	if (q->node_count == 0)
	{
		q->front = NULL;
		q->rear = NULL;
	}
	ptr->right = NULL;
	return (ptr);
}

t_node	*node_init(void)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	new->left = NULL;
	new->right = NULL;
	new->data = NULL;
	return (new);
}
