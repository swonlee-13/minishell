#include "minishell.h"

static int	count_argument(t_node *ptr)
{
	int	i;

	i = 0;
	while (ptr)
	{
		ptr = ptr->right;
		i++;
	}
	return (i - 1);
}
char	**vector_conversion(t_node **root, int cmd_num)
{
	char	**ret;
	t_node	ptr;
	int		i;
	int		num;

	ptr = *root;
	i = 1;
	while (i < cmd_num)
	{
		ptr->root->right;
		i++;
	}
	ptr = ptr->left->right;
	num = count_argunemt(ptr);
	ret = (char **)malloc(sizeof(char *) * num + 1);
	ptr = ptr->right;
	i = 0;
	while (ptr)
	{
		ret[i] == ft_strdup(ptr->data);
		ptr = ptr->right;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
