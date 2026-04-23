/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 09:28:57 by hbray             #+#    #+#             */
/*   Updated: 2026/04/23 15:51:28 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	init_signal_heredoc(void)
{
	struct sigaction	sig_heredoc;
	struct sigaction	ignore_quit;

	sigemptyset(&sig_heredoc.sa_mask);
	sigaddset(&sig_heredoc.sa_mask, SIGINT);
	sig_heredoc.sa_handler = signal_heredoc;
	sig_heredoc.sa_flags = 0;
	sigaction(SIGINT, &sig_heredoc, NULL);
	sigemptyset(&ignore_quit.sa_mask);
	ignore_quit.sa_handler = SIG_IGN;
	ignore_quit.sa_flags = 0;
	sigaction(SIGQUIT, &ignore_quit, NULL);
}

void	signal_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		g_signal_status = 130;
	}
}
