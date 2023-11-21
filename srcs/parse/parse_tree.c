#include "parse.h"

void	create_pipeline(t_tree *tree, int cmd_num)
{

}

void	tree_init(t_tree *tree)
{
	tree = (t_tree *)malloc(sizeof(t_tree));
	tree->root = NULL;
	tree->pipe_count = 0;
	return (tree);
}

t_tree	switch_to_tree(t_queue *q)
{
	t_tree	*tree;

	tree = tree_init(tree);
	if (q == NULL)
		return (tree);
	create_pipeline(tree, 1);
	
}
