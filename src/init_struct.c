/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 11:45:10 by hbray             #+#    #+#             */
/*   Updated: 2026/03/24 14:37:19 by asauvage         ###   ########.fr       */
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
	token->pre = NULL;
	token->token = NULL;
	token->next = NULL;
	return (token);
}
