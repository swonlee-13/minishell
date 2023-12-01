/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 22:35:19 by yeolee2           #+#    #+#             */
/*   Updated: 2023/12/01 22:57:53 by yeolee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void sig_handler(int signo){
    (void)signo;

    printf("\n");
    if(rl_on_new_line() == -1)
        exit(-1);
    rl_replace_line("", 1);
    rl_redisplay();
}

void init_sig(){
    signal(SIGINT, sig_handler);

}

/*
*/