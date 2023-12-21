/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 22:36:55 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/20 17:46:08 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

static char	*get_env_path(char **cmd, char **env)
{
	char	*path;

	path = get_env_data(env, "PATH");
	if (path == NULL)
	{
		g_exit_code = 127;
		printf("minishell: %s: No such file or directory\n", cmd[0]);
		exit(g_exit_code);
	}
	return (path);
}

char	*check_access(char **path, char *cmd)
{
	int		idx;
	char	*tmp;

	idx = 0;
	while (path[idx])
	{
		tmp = ft_strjoin(path[idx], cmd);
		if (!access(tmp, X_OK))
		{
			free(cmd);
			ft_free(path);
			return (tmp);
		}
		free(tmp);
		idx++;
	}
	ft_free(path);
	free(cmd);
	return (NULL);
}

char	*get_command_path(char **cmd, char **env)
{
	char	*tmp;
	char	*ret;
	char	**path;

	if (cmd == NULL || *cmd == NULL || cmd[0][0] == '\0')
		return (NULL);
	if (cmd[0][0] == '/' || \
		(cmd[0][0] == '.' && cmd[0][1] == '/'))
		if (!access(*cmd, X_OK))
			return (*cmd);
	path = ft_split(get_env_path(cmd, env), ':');
	tmp = ft_strjoin("/", *cmd);
	ret = check_access(path, tmp);
	if (ret)
	{
		free(*cmd);
		return (ret);
	}
	return (*cmd);
}

int	count_commands(t_node *root)
{
	t_node	*ptr;
	int		cnt;

	ptr = root;
	cnt = 0;
	while (ptr)
	{
		ptr = ptr->right;
		cnt++;
	}
	return (cnt);
}
