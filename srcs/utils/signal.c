/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 22:35:19 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/13 17:47:56 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int g_exit_code;

void    prompt_sigint_handler(int signum)
{
    (void)signum;
    printf("\n");
    rl_replace_line("", 1);
    rl_on_new_line();
    rl_redisplay();
}

void    child_sigint_handler(void)
{
    // signal(SIGINT, SIG_DFL);
    // printf("\n");
}

void    heredoc_sigint_handler(int signum)
{
    (void)signum;
    close(STDIN_FILENO);
    g_exit_code = 1;
    printf("\n");
}

void    init_signal()
{
    // rl_catch_signals = 0;
    signal(SIGINT, prompt_sigint_handler);
    signal(SIGQUIT, SIG_IGN);}
