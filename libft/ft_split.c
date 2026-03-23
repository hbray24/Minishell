/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:32:13 by asauvage          #+#    #+#             */
/*   Updated: 2025/12/02 14:09:21 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_w(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	count;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] && s[i] == c)
			i++;
		j = i;
		while (s[i] && s[i] != c)
			i++;
		if (j < i)
			count++;
	}
	return (count);
}

static int	free_memo(char **res, int pos)
{
	if (res[pos] != NULL)
		return (1);
	while (pos >= 0)
	{
		free(res[pos]);
		pos--;
	}
	free(res);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		i[3];

	res = malloc(sizeof(char *) * (count_w(s, c) + 1));
	if (res == NULL)
		return (0);
	i[1] = 0;
	i[2] = 0;
	while (s[i[1]] != '\0')
	{
		while (s[i[1]] && s[i[1]] == c)
			i[1]++;
		i[0] = i[1];
		while (s[i[1]] && s[i[1]] != c)
			i[1]++;
		if (i[0] < i[1])
		{
			res[i[2]] = ft_substr(s, i[0], i[1] - i[0]);
			if (free_memo(res, i[2]++) != 1)
				return (0);
		}
	}
	res[i[2]] = 0;
	return (res);
}
