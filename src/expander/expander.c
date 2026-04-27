/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 11:30:51 by hbray             #+#    #+#             */
/*   Updated: 2026/04/27 13:51:20 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	delete_quote(char **str)
{
	char	*res;
	int		i;
	int		j;
	char	quote;

	i = 0;
	quote = 0;
	j = 0;
	res = alloc_new_str(ft_strlen(*str) - 1);
	if (!res)
		return (-1);
	while ((*str)[i])
	{
		if (!quote && ((*str)[i] == '\'' || (*str)[i] == '\"'))
			quote = (*str)[i++];
		else if ((*str)[i] == quote)
			i++;
		else
			res[j++] = (*str)[i++];
	}
	res[j] = '\0';
	free(*str);
	*str = res;
	return ((quote == '\"'));
}

char	*realloc_token(char *str, int start, int len_var, char *value)
{
	int		i;
	int		k;
	char	*new_str;

	new_str = alloc_new_str(ft_strlen(str) + (ft_strlen(value) - len_var));
	if (!new_str)
		return (NULL);
	i = 0;
	k = 0;
	while (str[k])
	{
		if (k == start - 1)
		{
			while (value && *value)
				new_str[i++] = *value++;
			if (!value && !ft_isalpha(str[k + 1]) && str[k + 1] != '_')
				new_str[i++] = '$';
			k += len_var + 1;
		}
		if (str[k])
			new_str[i++] = str[k++];
	}
	free(str);
	new_str[i] = '\0';
	return (new_str);
}

char	*expand_env_var(char *str, t_env *env, int *i)
{
	char	*sub_str;
	char	*tmp;
	int		j;
	int		val_len;

	val_len = 0;
	(*i)++;
	j = *i;
	if (!ft_isalpha(str[*i]) && str[*i] != '_')
		return (str);
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
	sub_str = ft_substr(str, j, *i - j);
	if (!sub_str)
		return (NULL);
	tmp = search_value(sub_str, env);
	free(sub_str);
	if (tmp)
		val_len = ft_strlen(tmp);
	str = realloc_token(str, j, *i - j, tmp);
	*i = (j - 1) + val_len;
	return (str);
}

int	expander(char **cmd, t_env *env)
{
	int	status;
	int	i;
	int	was_quote;

	status = 1;
	i = 0;
	while (cmd && cmd[i])
	{
		was_quote = 0;
		if (ft_strchr(cmd[i], '\"') || ft_strchr(cmd[i], '\''))
			was_quote = 1;
		status = single_or_double_q(&cmd[i]);
		if (status == -1)
			return (0);
		if (status)
			cmd[i] = search_variable(cmd[i], env);
		if (cmd[i][0] == '\0' && was_quote == 0)
			cmd = del_null_str(cmd, &i);
		i++;
	}
	return (1);
}

int	expander_simple_array(char **str, t_env *env)
{
	int	status;
	int	i;
	int	was_quote;

	status = 1;
	i = 0;
	was_quote = 1;
	if (!str || !*str)
		return (1);
	if (ft_strchr(*str, '\"') || ft_strchr(*str, '\''))
		was_quote = 1;
	status = single_or_double_q(str);
	if (status == -1)
		return (0);
	if (status)
		*str = search_variable(*str, env);
	if ((*str)[0] == '\0' && was_quote == 0)
	{
		free(*str);
		*str = NULL;
	}
	i++;
	return (1);
}
