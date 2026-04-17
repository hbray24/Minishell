/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_ctr-\.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:52:48 by hbray             #+#    #+#             */
/*   Updated: 2026/04/17 15:56:20 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	apply_term(int action, struct termios *back_up)
{
	struct termios	term;

	if (action == 0)
	{
		term = *back_up;
		term.c_cc[VQUIT] = _POSIX_VDISABLE;
		if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		{
			perror("tcsetattr");
			return ;
		}
	}
	else if (action == 1)
		if (tcsetattr(STDIN_FILENO, TCSANOW, back_up) == -1)
			perror ("tcsetattr");
}

void	gestion_term(int action)
{
	static struct termios	back_up;
	static int				save;

	if (save == 0)
	{
		if (tcgetattr(STDIN_FILENO, &back_up) == -1)
		{
			perror("tcgettattr");
			return ;
		}
		save = 1;
	}
	apply_term(action, &back_up);
}
