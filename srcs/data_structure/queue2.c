/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <seongwol@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 19:52:53 by seongwol          #+#    #+#             */
/*   Updated: 2023/12/16 19:53:30 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	empty_queue(t_queue *q)
{
	while (q->node_count != 0)
		dequeue(q);
}

void	queue_init(t_queue *q)
{
	q->front = NULL;
	q->rear = NULL;
	q->node_count = 0;
	q->total_cmd_num = 0;
}
