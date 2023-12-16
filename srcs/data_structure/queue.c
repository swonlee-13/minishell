/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 19:20:39 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/16 19:14:38 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	queue_init(t_queue *q)
{
	q->front = NULL;
	q->rear = NULL;
	q->node_count = 0;
	q->total_cmd_num = 0;
}

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

void	print_queue(t_queue *q)
{
	t_node *ptr;

	ptr = q->front;
	while (ptr)
	{
		printf("[%s]", ptr->data);
		printf("->");
		ptr = ptr->right;
	}
	printf("NULL");
}

void	empty_queue(t_queue *q)
{
	while (q->node_count != 0)
		dequeue(q);
}

t_node	*node_init(void)
{
	t_node *new;

	new = malloc(sizeof(t_node));
	new->left = NULL;
	new->right = NULL;
	new->data = NULL;
	return (new);
}
