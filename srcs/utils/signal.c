/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 22:35:19 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/13 01:28:36 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    prompt_sigint_handler(int signum)
{
    (void)signum;
    printf("\n");
    rl_replace_line("", 1);
    rl_on_new_line();
    rl_redisplay();
}

void    heredoc_sigint_handler(int signum)
{
    (void)signum;
    printf("\n");
    rl_replace_line("", 1);
    rl_on_new_line();
    rl_redisplay();
}

void    init_signal()
{
    // rl_catch_signals = 0;
    signal(SIGINT, prompt_sigint_handler);
    signal(SIGQUIT, SIG_IGN);}
