#include "minishell.h"

t_node	*find_redirection_root(t_node *root, int cmd_num)
{
	t_node	*ptr;
	int		i;

	ptr = root;
	i = 1;
	while (i < cmd_num)
	{
		ptr = ptr->right;
		i++;
	}
	ptr = ptr->left->left;
	return (ptr);
}
