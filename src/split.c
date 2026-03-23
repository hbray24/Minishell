/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 13:00:48 by asauvage          #+#    #+#             */
/*   Updated: 2026/03/23 18:04:40 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_issep(char *str, int *i)
{
	if (str[*i] && (str[*i] == '|' || str[*i] == '<' || str[*i] == '>'))
	{
		if ((!ft_strncmp(&str[*i], "<<", 2) || !ft_strncmp(&str[*i], ">>", 2)))
			(*i) += 2;
		else
			(*i)++;
		return (1);
	}
	return (0);
}

int	ft_issep2(char *str, int i)
{
	if (str[i] && (str[i] == '|' || str[i] == '<' || str[i] == '>'))
		return (1);
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
		if (!str[i])
			break ;
		if (!ft_issep2(str, i))
			nb_word++;
		while (str[i] && !ft_isspace(str[i]))
		{
			if (str[i] == '\'' || str[i] == '\"')
				i = skip_w_quote(str, i);
			if (ft_issep(str, &i))
			{
				nb_word++;
				break;
			}
			i++;
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
	while (str && str[end] && !ft_isspace(str[end]) && !ft_issep2(str, end))
	{
		if (str[end] == '\'' || str[end] == '\"')
			end = skip_w_quote(str, end);
		end++;
	}
	if (ft_issep2(str, *start))
		ft_issep(str, &end);
	return (end - *start);
}

char	*ft_dup_w(char *res, char *str, int *i)
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
		res[w] = ft_dup_w(res[w], str, &i);
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
