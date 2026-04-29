/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_nb_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 09:10:04 by hbray             #+#    #+#             */
/*   Updated: 2026/04/29 09:53:10 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_nb_quote(char *str)
{
	int		i;
	int		nb_quote;
	char	quote;

	i = 0;
	nb_quote = 0;
	quote = 0;
	while (str[i])
	{
		if (quote != str[i] && (str[i] == '\'' || str[i] == '\"'))
		{
			nb_quote += 1;
			quote = str[i];
			i++;
		}
		if (str[i] && quote == str[i])
		{
			nb_quote += 1;
			quote = 0;
		}
		i++;
	}
	return (nb_quote);
}
