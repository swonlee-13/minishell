#include "parse.h"

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

t_node	*switch_to_tree(t_queue *q)
{
	int		i;
	t_node	*root;
	t_node	*tmp;

	i = 0;
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
			tmp = dequeue(q);
		}
		tree_insert(&root, tmp);
		tmp = dequeue(q);
	}
	return (root);
}
