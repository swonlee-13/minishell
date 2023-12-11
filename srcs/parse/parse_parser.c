/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 19:22:00 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/11 22:49:30 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_type	node_type_setter(char *token_string, int i)
{
	while (token_string[i] == 'D' || token_string[i] == '$' \
			|| token_string[i] == 'S')
		i++;
	if (token_string[i] == 'I' || token_string[i] == 'O')
		return (PASS);
	else if (token_string[i] == 'P')
		return (PIPE);
	else if (token_string[i] == 'A')
		return (ARGS);
	else if (token_string[i] == 'F')
		return (REDIR_SINGLE_IN);
	else if (token_string[i] == 'E')
		return (REDIR_SINGLE_OUT);
	else if (token_string[i] == 'G')
		return (REDIR_DOUBLE_OUT);
	else if (token_string[i] == 'H')
		return (REDIR_DOUBLE_IN);
	else if (token_string[i] == '\0')
		return (PASS);
	else
		write(1,"error type setter\n", 18);
	return (PASS);
}

int	command_enqueue_indexing(char *token_string, int i)
{
	char	tmp;

	if (token_string[i] == 'P' || ft_is_op_redirection(token_string[i]))
	{
		tmp = token_string[i];
		while (token_string[i] == tmp)
			i++;
		return (i);
	}
	else
	{
		while (token_string[i] != '\0' && !ft_is_op_token(token_string[i]))
			i++;
		return (i);
	}
}

void	command_enqueue(t_queue *q, char *cmd, char *token_string)
{
	t_node	*node;
	int	start;
	int	i;

	i = 0;
	while (token_string[i] != '\0')
	{
		node = node_init();
		while (token_string[i] == ' ')
			i++;
		start = i;
		i = command_enqueue_indexing(token_string, i);
		node->type = node_type_setter(token_string, start);
		if (node->type != PASS)
		{
			node->data = ft_substr(cmd, start, i - start);
			node_enqueue(q, node);
			if (node->type == PIPE)
				q->total_cmd_num++;
		}
		else
			free(node);
	}
	if (q->front != NULL)
		q->total_cmd_num++;
}

char	*make_token_string(char *cmd)
{
	char	*token_string;

	token_string = tokenizer(cmd);
	if (token_lexer(cmd, token_string) == SYNTAX_ERROR)
	{
		write(1, "syntax error\n", 13);
		free(token_string);
		return (NULL);
	}
	token_setter(cmd, token_string);
	return (token_string);
}

t_node *parser(char *cmd, char **env_copy)
{
	char	*token_string;
	t_queue *q;
	t_node	*root;

	token_string = make_token_string(cmd);
	if(token_string == NULL)
		return (NULL);
	q = (t_queue *)malloc(sizeof(t_queue));
	queue_init(q);
	command_enqueue(q, cmd, token_string);
	free(token_string);
	node_data_formatting(q, env_copy);
	if (q->front == NULL)
	{
		free(q);
		return (NULL);
	}
	root = switch_to_tree(q);
	free(q);
	return (root);
}
