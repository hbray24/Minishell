/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 13:49:08 by hbray             #+#    #+#             */
/*   Updated: 2026/05/01 17:12:26 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**del_null_str(char **cmd, int *i)
{
	int	j;

	free(cmd[*i]);
	j = *i;
	while (cmd[j])
	{
		cmd[j] = cmd[j + 1];
		j++;
	}
	return (cmd);
}

char	*remove_quote(char **str, char *res)
{
	char	quote;
	char	quote2;
	int		i;
	int		j;

	i = 0;
	j = 0;
	quote2 = 0;
	quote = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == quote2 && i++)
			quote2 = 1;
		if (!quote2 && !quote && ((*str)[i] == '\'' || (*str)[i] == '\"'))
			quote = (*str)[i++];
		else if (!quote2 && (*str)[i] == quote && i++)
			quote2 = 1;
		if (quote2 && ((*str)[i] == '\'' || (*str)[i] == '\"'))
			quote2 = (*str)[i];
		else if ((*str)[i])
			res[j++] = (*str)[i++];
		else
			i++;
	}
	printf("%d, c=[%d]\n", j, res[j - 1]);
	res[j] = '\0';
	return (res);
}
