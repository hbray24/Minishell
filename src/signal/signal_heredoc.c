/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 09:28:57 by hbray             #+#    #+#             */
/*   Updated: 2026/04/23 09:56:21 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	init_signal_heredoc(void)
{
	struct sigaction	sig_action;
	struct sigaction	ignore_quit;

	sigemptyset(&sig_action.sa_mask);
	sigaddset(&sig_action.sa_mask, SIGINT);
	sig_action.sa_handler = signal_heredoc;
	sigaction(SIGINT, &sig_action, NULL);
	sigemptyset(&ignore_quit.sa_mask);
	ignore_quit.sa_handler = SIG_IGN;
	ignore_quit.sa_flags = 0;
	sigaction(SIGQUIT, &ignore_quit, NULL);
}

void	signal_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_status = 130;
		close(STDIN_FILENO);
		write(1, "\n", 1);
	}
}
