/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 22:35:19 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/21 19:39:26 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	prompt_sigint_handler(int signum)
{
	(void)signum;
	printf("\n");
	rl_replace_line("", 1);
	g_exit_code = 1;
	rl_on_new_line();
	rl_redisplay();
}

void	heredoc_sigint_handler(int signum)
{
	(void)signum;
	close(STDIN_FILENO);
	g_exit_code = 259;
	printf("\n");
}

void	init_signal(void)
{
	signal(SIGINT, prompt_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
