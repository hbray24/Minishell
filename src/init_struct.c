/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 11:45:10 by hbray             #+#    #+#             */
/*   Updated: 2026/04/02 14:05:25 by hbray            ###   ########.fr       */
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
		exit(1);
	}
	ft_memset(token, 0, sizeof(t_token));
	return (token);
}
