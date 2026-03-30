/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 11:45:10 by hbray             #+#    #+#             */
/*   Updated: 2026/03/30 17:16:56 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

t_token	*malloc_struct(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		write(2, "hbray: Malloc\n", 15);
		exit (1);
	}
	memset(token, 0, sizeof(t_token));
	return (token);
}
