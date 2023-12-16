/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 22:36:55 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/16 19:55:21 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_command_path(char **cmd, char **env)
{
	int		idx;
	char	*tmp1;
	char	*tmp2;
	char	**path;

	if (cmd[0][0] == '/' || \
		(cmd[0][0] == '.' && cmd[0][1] == '/'))
		if (!access(*cmd, X_OK))
			return (*cmd);
	path = ft_split(get_env_data(env, "PATH"), ':');
	tmp1 = ft_strjoin("/", *cmd);
	idx = -1;
	while (path[++idx])
	{
		tmp2 = ft_strjoin(path[idx], tmp1);
		if (!access(tmp2, X_OK))
		{
			free(tmp1);
			ft_free(path);
			return (tmp2);
		}
		free(tmp2);
	}
	free(tmp1);
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
