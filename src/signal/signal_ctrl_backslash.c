/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_ctrl_backslash.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:52:48 by hbray             #+#    #+#             */
/*   Updated: 2026/05/02 15:26:00 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	apply_term(int action, struct termios *back_up)
{
	struct termios	term;

	if (action == 0)
	{
		term = *back_up;
		term.c_cc[VQUIT] = _POSIX_VDISABLE;
		if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
			return (perror("Minishell :tcsetattr"), 1);
	}
	else if (action == 1)
		if (tcsetattr(STDIN_FILENO, TCSANOW, back_up) == -1)
			return (perror("Minishell :tcsetattr"), 1);
	return (0);
}

int	gestion_term(int action)
{
	static struct termios	back_up;
	static int				save;

	// if (!isatty(STDIN_FILENO))
	// 	return (0);
	if (save == 0)
	{
		if (tcgetattr(STDIN_FILENO, &back_up) == -1)
		{
			perror("Minishell :tcgettattr");
			return (1);
		}
		save = 1;
	}
	if (!apply_term(action, &back_up))
		return (1);
	return (0);
}
