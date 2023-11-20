#include "parse.h"

t_node	*tree_insert(t_node *root, t_type type, char *token)
{
	if (root == NULL)
	{
		root = (t_node *)malloc(sizeof(t_node));
		root->left = NULL;
		root->right = NULL;
		root->data = token;
		root->type = type;
		return (root);
	}
	else
	{
		if (type < root->type)
			tree_insert(root->left, type, token);
		else
			tree_insert(root->right, type, token);
	}
}

void	print(t_node *root)
{
	if (root == NULL)
		return ;
	print(root->left);
	printf("node data = %s, node type = %d\n", root->data, root->type);
	print(root->right);
}

t_node *preorder_collect(t_node *root, t_queue *q)	//tree 분석이 끝나면 트리node 를 queue 에 순서대로 담는다.
{
	if (root == NULL)
		return (NULL);
	enqueue(q, root->data);
}
