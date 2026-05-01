/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 11:30:51 by hbray             #+#    #+#             */
/*   Updated: 2026/05/01 17:14:02 by asauvage         ###   ########.fr       */
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
	// printf("len: [%d], index i: [%d]\n", len, *i);
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
		if (cmd[i] && quote == cmd[i])
			quote = 0;
		else if (cmd[i] && ++i)
			len++;
	}
	return (len);
}

int	replace_by_status(char *str, int j, int status)
{
	char	*tmp_status;
	int		k;

	k = 0;
	tmp_status = ft_itoa(status);
	if (!tmp_status)
		return (perror("Minishell"), -1);
	while (tmp_status[j])
		str[j++] = tmp_status[k++];
	free(tmp_status);
	return (1);
}

int	replace_var_value(char *res, char *str, int *i, t_env *env)
{
	char	*variable;
	char	*tmp;
	int		start;
	int		j;

	start = *i;
	j = 0;
	if (str[*i] == '?' && (*i)++)
		return (replace_by_status(res, j, env->status));
	while (str && str[*i] && str[*i] != '\'' && str[*i] != '\"')
		(*i)++;
	tmp = ft_substr(str, start, *i - start);
	if (!tmp)
		return (-1);
	variable = search_value(tmp, env);
	j = 0;
	free(tmp);
	while (variable && variable[j])
	{
		res[j] = variable[j];
		j++;
	}
	res[j] = '\0';
	return (j);
}

char	*replace_cmd(char *str, t_env *env, char *res, char quote)
{
	int		i;
	int		status;
	int		j;

	j = 0;
	i = 0;
	while (str && str[i])
	{
		status = 0;
		if (!quote && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i++];
		if (str[i] && quote != '\'' && str[i] == '$' && ++i)
			status = replace_var_value(&res[j], str, &i, env);
		if (status == -1)
			return (free(str), free(res), NULL);
		j += status;
		if (str[i] && quote != str[i])
			res[j++] = str[i++];
		if (str[i] && quote == str[i] && ++i)
			quote = 0;
	}
	free(str);
	return (res);
}

int	expander(char **cmd, t_env *env)
{
	int		i;
	int		len;
	char	*res;
	char	quote;

	i = 0;
	while (cmd && cmd[i])
	{
		quote = 0;
		len = calc_len(cmd[i], env);
		if (len == -1)
			return (0);
		res = ft_calloc(len + 1, sizeof(char));
		if (!res)
			return (perror("Minishell"), 0);
		cmd[i] = replace_cmd(cmd[i], env, res, quote);
		if (!cmd[i])
			return (0);
		i++;
	}
	return (1);
}

int	expander_simple_array(char **str, t_env *env)
{
	char	quote;
	char	*res;
	int		len;

	if (!str || !*str)
		return (1);
	quote = 0;
	len = calc_len(*str, env);
	if (len == -1)
		return (0);
	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (perror("Minishell"), 0);
	res = replace_cmd(*str, env, res, quote);
	if (!*res)
		return (0);
	if (res[0] == '\0')
	{
		free(res);
		*str = NULL;
	}
	*str = res;
	return (1);
}
