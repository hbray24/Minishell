/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 13:00:48 by asauvage          #+#    #+#             */
/*   Updated: 2026/03/26 09:09:29 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	next_token(char *str, int i)
{
	if (ft_issep(str, &i, 1))
		return (i);
	while (str[i] && !ft_isspace(str[i]) && !ft_issep(str, &i, 0))
	{
		if (str[i] == '\'' || str[i] == '\"')
			i = skip_w_quote(str, i);
		i++;
	}
	return (i);
}

int	count_token(char *str)
{
	int	i;
	int	nb_word;

	i = 0;
	nb_word = 0;
	while (str && str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (str[i])
		{
			nb_word++;
			i = next_token(str, i);
		}
	}
	return (nb_word);
}

int	len_word(char *str, int *start)
{
	int	end;

	while (ft_isspace(str[*start]))
		(*start)++;
	end = *start;
	while (str && str[end] && !ft_isspace(str[end]) && !ft_issep(str, &end, 0))
	{
		if (str[end] == '\'' || str[end] == '\"')
			end = skip_w_quote(str, end);
		end++;
	}
	if (ft_issep(str, start, 0))
		ft_issep(str, &end, 1);
	return (end - *start);
}

char	*ft_dup_token(char *res, char *str, int *i)
{
	int	len_w;
	int	start;

	len_w = len_word(str, i);
	res = malloc(sizeof(char) * (len_w + 1));
	if (!res)
	{
		write(2, "hbray: Malloc\n", 15);
		return (NULL);
	}
	start = 0;
	while (start < len_w)
	{
		res[start] = str[*i];
		start++;
		(*i)++;
	}
	res[start] = '\0';
	return (res);
}

char	**split(char *str)
{
	int		i;
	int		w;
	int		nb_word;
	char	**res;

	nb_word = count_token(str);
	res = malloc(sizeof(char *) * (nb_word + 1));
	if (!res)
		return (NULL);
	i = 0;
	w = 0;
	while (w < nb_word)
	{
		res[w] = ft_dup_token(res[w], str, &i);
		if (!res[w])
		{
			free_array(res);
			return (NULL);
		}
		w++;
	}
	res[w] = NULL;
	return (res);
}
