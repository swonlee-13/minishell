#include "parse.h"

void	create_pipeline(t_tree *tree, int cmd_index)
{
	t_node	*node;
	int		i;

	i = 0;
	node = tree->root;
	while (i < cmd_index - 1)
	{
		node = node->right; 
		i++;
	}
	tree_insert(node, CMD, NULL);
	tree_insert(node, REDIRECTION_ROOT, NULL);
	tree_insert(node, ARGUMENT_ROOT, NULL);
}

void	tree_init(t_tree *tree)
{
	tree = (t_tree *)malloc(sizeof(t_tree));
	tree_insert(tree->root, PIPE, NULL);
	tree->pipe_count = 0;
	return ;
}

void	token_insert(t_tree *tree, t_queue *q, int cmd_idx)
{
	t_node	*data;
	t_node	*node;
	int		i;

	i = 0;
	data = NULL;
	node = tree->root;
	while (i < cmd_idx)
	{
		node = node->right;
		i++;
	}
	while (data->type != PIPE)
	{
		data = dequeue(q);
		tree_insert(node, data->type, data->data);
		free(data->data);
		free(data);
	}
	free(data->data);
	free(data);
	return ;
}

t_tree	*switch_to_tree(t_queue *q)
{
	t_tree	*tree;
	int		i;

	i = 0;
	tree_init(tree);
	if (q == NULL)
		return (tree);
	else
		i++;
	while (i < q->total_cmd_num)
	{
		create_pipeline(tree, i);
		token_insert(tree, q, i);
		i++;
	}
	if (q->front != NULL)
		printf("%d, %s error", __LINE__, __FILE__); //test
	return (tree);
}
