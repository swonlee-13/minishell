#include "minishell.h"
#include "parse.h"

char	*create_here_doc_file(t_node *node)
{
	char		*file_name;
	int			ret;
	static int	number;

	number++;
	file_name = ft_strjoin("/tmp/minishell/my_here_doc", ft_itoa(number));
	while (access(file_name, F_OK) != SUCCESS)
	{
		free(file_name);
		number++;
		file_name = ft_strjoin("/tmp/minishell/my_here_doc", ft_itoa(number));
	}
	node->fd = open(filename, O_WRONLY | O_CREAT | O_EXCL | O_TRUNK);
	return (file_name);
}

void	write_here_doc(t_node *node, char **env_copy)
{
	char	*end;
	char	*buffer;

	end = ft_strjoin(node->data, "\n");
	while (1)
	{
		write(1, "heredoc> ", 9);
		buffer = get_next_line(STDIN_FILENO);
		if (*buffer == 0 || ft_strcmp(buffer, end) == 0)
			break;
		buffer = here_doc_formatting(buffer, env_copy)
		ft_putstr_fd(buffer, node->fd);
		free(buffer);
	}
	free(buffer);
	free(end);
}

void	activate_here_doc(t_node *node, char **env_copy);
{
	char	*file_name;

	file_name = create_here_doc_file(root);
	if (node->fd == -1)
	{
		perror(errno); //TODO: 에러 관련 처리 합시다
		return(errno); //TODO: 에러 관련 처리 합시다
	}
	write_here_doc(node);
	close(node->fd);
	node->fd = open(file_name, O_RDONLY);
	if (node->fd == -1)
	{
		perror(errno); //TODO: 에러 관련 처리 합시다
		return(errno); //TODO: 에러 관련 처리 합시다
	}
	unlink(file_name);
	free(file_name);
}

void	open_here_doc(t_node *root, char **env_copy)
{
	if (root->type == REDIR_DOUBLE_IN)
		activate_here_doc(root, env_copy);
	open_here_doc(root->left);
	open_here_doc(root->right);
}
