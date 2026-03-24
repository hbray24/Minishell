/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 13:10:21 by asauvage          #+#    #+#             */
/*   Updated: 2026/03/24 11:21:58 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		free(str[i++]);
	if (str)
		free(str);
}

void	clear_token(t_token *token)
{
	t_token	*tmp;

	token = first_token(token);
	while (token)
	{
		if (token->token)
			free(token->token);
		tmp = token;
		token = token->next;
		free(tmp);
	}
}
