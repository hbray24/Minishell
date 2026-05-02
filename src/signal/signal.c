/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 13:12:06 by hbray             #+#    #+#             */
/*   Updated: 2026/05/02 16:00:05 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_signal_status;

void	manages_signal(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		g_signal_status = 130;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_signal(void)
{
	struct sigaction	sig_action;

	signal(SIGPIPE, SIG_IGN);
	sigemptyset(&sig_action.sa_mask);
	sigaddset(&sig_action.sa_mask, SIGINT);
	sigaddset(&sig_action.sa_mask, SIGQUIT);
	sig_action.sa_handler = manages_signal;
	sig_action.sa_flags = 0;
	sigaction(SIGINT, &sig_action, NULL);
	sigaction(SIGQUIT, &sig_action, NULL);
}

void	ignore_signal(void)
{
	struct sigaction	ignore;

	ignore.sa_handler = SIG_IGN;
	sigemptyset(&ignore.sa_mask);
	ignore.sa_flags = 0;
	sigaction(SIGINT, &ignore, NULL);
	sigaction(SIGQUIT, &ignore, NULL);
}

void	restore_signal(void)
{
	struct sigaction	restore;

	restore.sa_handler = manages_signal;
	sigemptyset(&restore.sa_mask);
	restore.sa_flags = 0;
	sigaction(SIGINT, &restore, NULL);
	sigaction(SIGQUIT, &restore, NULL);
}
