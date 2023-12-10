/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 22:35:19 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/10 01:04:42 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    child_sigint_handler(int signum)
{
    (void)signum;
    exit(EXIT_FAILURE);
}

void    parent_sigint_handler(int signum)
{
    (void)signum;
    
    printf("\n");
    // if (rl_on_new_line() == -1)
        // exit(-1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

void sig_pa(int signo)
{
    if (signo == SIGINT){
        printf("^C\n");
    }
    else if (signo == SIGTERM){
        printf("\n");
    }
}

void signal_heredoc(int signo){
    printf("\n");
    
}

void init_sig()
{
    // signal(SIGINT, SIG_IGN);
    rl_catch_signals = 0;
    signal(SIGINT, parent_sigint_handler);
    signal(SIGQUIT, SIG_IGN);
}
