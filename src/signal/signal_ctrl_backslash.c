/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_ctrl_backslash.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:52:48 by hbray             #+#    #+#             */
/*   Updated: 2026/04/23 13:42:17 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	apply_term(int action, struct termios *back_up)
{
	struct termios	term;

	if (action == 0)
	{
		term = *back_up;
		term.c_cc[VQUIT] = _POSIX_VDISABLE;
		if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		{
			perror("Minishell :tcsetattr");
			return ;
		}
	}
	else if (action == 1)
		if (tcsetattr(STDIN_FILENO, TCSANOW, back_up) == -1)
			perror ("Minishell :tcsetattr");
}

void	gestion_term(int action)
{
	static struct termios	back_up;
	static int				save;

	if (save == 0)
	{
		if (tcgetattr(STDIN_FILENO, &back_up) == -1)
		{
			perror("Minishell :tcgettattr");
			return ;
		}
		save = 1;
	}
	apply_term(action, &back_up);
}
