/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 12:07:29 by asauvage          #+#    #+#             */
/*   Updated: 2026/04/21 11:38:46 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_issep(char *str, int *i, int index_go)
{
	if (str[*i] && (str[*i] == '|' || str[*i] == '<' || str[*i] == '>'))
	{
		if (index_go && (!ft_strncmp(&str[*i], "<<", 2) || !ft_strncmp(&str[*i],
					">>", 2)))
			(*i) += 2;
		else if (index_go)
			(*i)++;
		return (1);
	}
	return (0);
}

int	skip_w_quote(char *str, int i)
{
	char	quote;

	quote = str[i];
	i++;
	while (str[i] && str[i] != quote)
		i++;
	return (i);
}
