/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 11:30:51 by hbray             #+#    #+#             */
/*   Updated: 2026/04/14 14:57:51 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*search_key(char *key, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return(env->key);
		env = env->next;
	}
	return(NULL);
}

int	delete_quote(char **str)
{
	char	*res;
	int		i;
	int		j;
	char	quote;

	res = malloc(sizeof(char) * (ft_strlen(*str) - 1));
	if (!res)
	{
		perror("Minishell");
		return (-1);
	}
	i = 0;
	quote = 0;
	j = 0;
	while ((*str)[i])
	{
		if (!quote && ((*str)[i] == '\'' || (*str)[i] == '\"'))
			quote =(*str)[i++];
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

int	single_or_double_q(char **str)
{
	int	i;

	i = 0;
	while (str && *str && (*str)[i])
	{
		if ((*str)[i] == '\"')
			return (delete_quote(str));
		else if ((*str)[i] == '\'')
			return (delete_quote(str));
		i++;
	}
	return (1);
}

char	*realloc_token(char *str, int start, int len_var, char *value)
{
	int		len;
	int		i;
	int		j;
	int		k;
	char	*new_str;

	len = ft_strlen(str) + (ft_strlen(value) - len_var);
	new_str = malloc(sizeof(char) * (len + (len == 1)));
	if (!new_str)
	{
		perror("Minishell");
		return (NULL);
	}
	i = 0;
	j = 0;
	k = 0;
	while (str[k])
	{
		if (k == start - 1)
		{
			while (value && value[j])
				new_str[i++] = value[j++];
			if (!value && !ft_isalpha(str[k + 1]) && str[k + 1] != '_')
				new_str[i++] = '$';
			k += len_var + 1;
		}
		if (str[k])
			new_str[i++] = str[k++];
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*search_variable(char *str, t_env *env)
{
	char	*tmp;
	char	*sub_str;
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			tmp = ft_itoa(env->status);
			if (!tmp)
				return (NULL);
			str = realloc_token(str, i + 1, 2, tmp);
			free(tmp);
			if (!str)
				return (NULL);
			i += 2;
		}
		else if (str[i++] == '$')
		{
			j = i;
			if (!ft_isalpha(str[i]) && str[i] != '_')
				continue ;
			while (ft_isalnum(str[i]) || str[i] == '_')
				i++;
			sub_str = ft_substr(str, j, i - 1);
			if (!sub_str)
				return (NULL);
			tmp = search_value(sub_str, env);
			free(sub_str);
			str = realloc_token(str, j, i - j, tmp);
			free(tmp);
			if (!str)
				return (NULL);
		}
	}
	return (str);
}

int	expander(t_token *token, t_env *env)
{
	int	status;
	int	i;

	i = 0;
	status = 1;
	while (token)
	{
		status = single_or_double_q(&token->token);
		if (status == -1)
			return (0);
		if (status)
			token->token = search_variable(token->token, env);
		token = token->next;
	}
	return (1);
}
