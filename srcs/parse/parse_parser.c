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

	token_string = tokenizer(cmd);					//이 결과물을 printf 를 이용해서 cmd 와 비교해보면 1차 tokenizing 결과를 알 수 있음.
	if (token_lexer(cmd, token_string) == SYNTAX_ERROR)	//이 코드를 타면 redirection, quote 닫힘여부file path 없음, pipe 연속으로 들어오는 에러처리.
	{
		write(1, "syntax error\n", 13);
		free(token_string);
		return (NULL);
	}
	token_setter(cmd, token_string);			// 해당 코드를 지나면 token의 성격에 따라서 세분화 된 token_string을 얻을 수 있음.
	return (token_string);
}

void    print_queue(t_queue *q);
void    print_queue_type(t_queue *q)
{
	t_node *node;

	node = q->front;
	printf("\n---------------------------\n");
	while (node)
	{
		printf("[%d]", node->pipe_index);
		printf(" -> ");
		node = node->right;
	}
	printf("NULL");
	printf("\n");
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

int main(int ac, char **av, char **env)
{
	(void)ac; (void)av;

	t_node	*tree;
	char	**cmd_vector;

	char *cmd = readline("minishell$> ");
	tree = parser(cmd, env);
	cmd_vector = vector_conversion(&tree, 1);
	for (int i = 0; cmd_vector[i]; i++)
		printf("%s\n", cmd_vector[i]);
	free_tree(tree);
	ft_free(cmd_vector);
	free(cmd);
}
