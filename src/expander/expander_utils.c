/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 16:28:35 by hbray             #+#    #+#             */
/*   Updated: 2026/05/02 12:29:26 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	len_status(int status)
{
	int		i;
	char	*tmp;

	tmp = ft_itoa(status);
	if (!tmp)
		return (perror("Minishell: len_status"), -1);
	i = 0;
	while (tmp[i])
		i++;
	free(tmp);
	return (i);
}

int	len_variable(char *cmd, int *i, t_env *env)
{
	int		len;
	char	*variable;
	int		start;

	len = 0;
	start = *i;
	if (cmd[*i] == '?')
		return (len_status(env->status));
	while (cmd && cmd[*i] && cmd[*i] != '\'' && cmd[*i] != '\"')
		(*i)++;
	variable = ft_substr(cmd, start, *i - start);
	if (!variable)
		return (-1);
	len = ft_strlen(search_value(variable, env));
	free(variable);
	return (len);
}

int	calc_len(char *cmd, t_env *env)
{
	int		i;
	char	quote;
	int		len;
	int		status;

	i = 0;
	quote = 0;
	len = 0;
	status = 0;
	while (cmd && cmd[i])
	{
		if (!quote && (cmd[i] == '\'' || cmd[i] == '\"'))
			quote = cmd[i++];
		if (cmd[i] && quote != '\'' && cmd[i] == '$' && ++i)
			status = len_variable(cmd, &i, env);
		if (status == -1)
			return (-1);
		len += status;
		if (cmd[i] && quote == cmd[i] && ++i)
			quote = 0;
		else if (cmd[i] && ++i)
			len++;
	}
	return (len);
}

char	*search_value(char *key, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*alloc_new_str(int len)
{
	char	*res;

	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (perror("Minishell :alloc_new_str"), NULL);
	return (res);
}
