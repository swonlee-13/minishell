/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 00:15:43 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/12 00:37:53 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_error_message(char **vector, char *error)
{
	char	*tmp1;
	char	*tmp2;
	char    *error_message;

	tmp1 = ft_strjoin(vector[0], ": ");
	tmp2 = ft_strjoin("minishell: ", tmp1);
	error_message = ft_strjoin(tmp2, error);
	free(tmp1);
	free(tmp2);
	ft_putstr_fd(error_message, 2);
	free(error_message);
}
