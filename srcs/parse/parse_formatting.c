/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_formatting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 19:21:43 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/01 19:21:46 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

char	*env_var_replace_sub(char *str, char **env)
{
	int		i;
	int		len;
	char	*res;

	i = 0;
	len = ft_strlen(str);
	while (env[i] != NULL)
	{
		if (ft_strncmp(str + 1, env[i], len - 2) == 0)
			break;
		i++;
	}
	if (env[i] == NULL)
		res = ft_strdup("");
	else
		res = ft_substr(env[i], len - 1, ft_strlen(env[i]));
	return (res);
}

char	*env_var_replace(char *str, char **env)
{
	char	*tmp;

//	if (ft_strcmp(str, "$?") == 0)
//	{
//		free(str);
//		str = 시그널 exit code 관련 int return value;
//	}
	if (str[0] != '$' || ft_strcmp(str, "$") == 0)
		return (str);
	else
	{
		tmp = ft_strjoin(str, "=");
		free(str);
		str = env_var_replace_sub(tmp, env);
		free(tmp);
		return (str);
	}
}

char	*r_n_r_double_quote(char *str, char **env)
{
	char	*res;
	char	**tmp;
	int		i;

	i = 0;
	if (str[0] == '"')
		res = ft_strtrim(str, "\"");
	else
		res = ft_strdup(str);
	free(str);
	tmp = shell_split_dollar(res);
	while (tmp[i] != NULL)
	{
		tmp[i] = env_var_replace(tmp[i], env);
		i++;
	}
	free(res);
	res = NULL;
	res = merge_splitted_cmd(tmp);
	ft_free(tmp);
	return (res);
}

void	remove_and_replace(char **strs, char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (strs[i] != NULL)
	{
		if (strs[i][0] == '$' && strs[i][1] == '"')
		{
			tmp = ft_strtrim(strs[i], "\"$");
			free(strs[i]);
			strs[i] = tmp;
		}
		else if (strs[i][0] == '\'')
		{
			tmp = ft_strtrim(strs[i], "'");
			free(strs[i]);
			strs[i] = tmp;
		}
		else if (strs[i][0] == '"' || strs[i][0] == '$')
			strs[i] = r_n_r_double_quote(strs[i], env);
		i++;
	}
}

char	*merge_splitted_cmd(char **strs)
{
	char	*res;
	char	*temp;
	int		i;

	i = 0;
	temp = NULL;
	while (strs[i] != NULL)
	{
		res = NULL;
		res = ft_strjoin(temp, strs[i]);
		free(temp);
		temp = res;
		i++;
	}
	return (res);
}

char	*string_formatting(char *str, char **env_copy)
{
	char	**tmp;
	char	*ret;

	ret = NULL;
	tmp = shell_split_quote(str);
	remove_and_replace(tmp, env_copy);
	ret = merge_splitted_cmd(tmp);
	ft_free(tmp);
	free(str);
	return (ret);
}

void	node_data_formatting(t_queue *q, char **env_copy)
{
	t_node	*node;
	char	*tmp;

	node = q->front;
	while (node)
	{
		tmp = node->data;
		node->data = string_formatting(tmp, env_copy);
		node = node->right;
	}
}
