/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 19:15:42 by asauvage          #+#    #+#             */
/*   Updated: 2026/05/02 19:16:10 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manages_signal_pipe(int sig)
{
	if (sig == SIGINT)
		g_signal_status = 130;
	if (sig == SIGQUIT)
		g_signal_status = 131;
}

void	init_ctrl_pipe(void)
{
	struct sigaction	pipe;

	pipe.sa_handler = manages_signal_pipe;
	sigemptyset(&pipe.sa_mask);
	pipe.sa_flags = 0;
	sigaction(SIGINT, &pipe, NULL);
	sigaction(SIGQUIT, &pipe, NULL);
}
