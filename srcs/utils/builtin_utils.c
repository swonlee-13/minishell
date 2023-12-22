/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 22:43:21 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/22 15:56:49 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin(char **command_vector, char ***env_copy)
{
	if (!ft_strcmp(command_vector[0], "cd"))
		change_directory(command_vector, env_copy);
	else if (!ft_strcmp(command_vector[0], "echo"))
		write_arg_to_stdout(command_vector);
	else if (!ft_strcmp(command_vector[0], "env"))
		print_env_list(*env_copy);
	else if (!ft_strcmp(command_vector[0], "exit"))
		terminate_program(command_vector);
	else if (!ft_strcmp(command_vector[0], "export"))
		set_export_attribute(env_copy, command_vector);
	else if (!ft_strcmp(command_vector[0], "pwd"))
		print_working_directory();
	else if (!ft_strcmp(command_vector[0], "unset"))
		unset_export_attribute(env_copy, command_vector);
}

int	is_builtin(char *command)
{
	if (command == NULL)
		return (FALSE);
	if (!ft_strcmp(command, "cd"))
		return (TRUE);
	else if (!ft_strcmp(command, "echo"))
		return (TRUE);
	else if (!ft_strcmp(command, "env"))
		return (TRUE);
	else if (!ft_strcmp(command, "exit"))
		return (TRUE);
	else if (!ft_strcmp(command, "export"))
		return (TRUE);
	else if (!ft_strcmp(command, "pwd"))
		return (TRUE);
	else if (!ft_strcmp(command, "unset"))
		return (TRUE);
	return (FALSE);
}
