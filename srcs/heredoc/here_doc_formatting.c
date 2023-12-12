/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_formatting.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 22:42:30 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/11 22:42:31 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*here_doc_formatting(char *str, char **env_copy)
{
	char	**tmp;
	char	*ret;
	int		i;

	i = 0;
	ret = NULL;
	if (str == NULL)
		return (NULL);
	tmp = shell_split_here_doc(str);
	while (tmp[i])
	{
		tmp[i] = env_var_replace(tmp[i], env_copy);
		i++;
	}
	ret = merge_splitted_cmd(tmp);
	ft_free(tmp);
	free(str);
	return (ret);
}
