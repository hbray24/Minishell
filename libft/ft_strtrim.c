/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:56:33 by asauvage          #+#    #+#             */
/*   Updated: 2025/12/02 14:10:05 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	verif(char s1, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (s1 == set[i])
			return (0);
		i++;
	}
	return (1);
}

static size_t	last_index(const char *s1, const char *set)
{
	size_t	j;

	j = ft_strlen(s1) - 1;
	while (j > 0 && verif(s1[j], set) == 0)
		j--;
	if (j == 0)
		return (0);
	return (j + 1);
}

static size_t	first_index(const char *s1, const char *set)
{
	size_t	i;

	i = 0;
	while (verif(s1[i], set) == 0)
		i++;
	if (i == ft_strlen(s1))
		i = 0;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	size_t	i;
	size_t	j;
	size_t	len;

	len = last_index(s1, set) - first_index(s1, set);
	res = malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (0);
	res[0] = '\0';
	if (len == 0)
		return (res);
	i = first_index(s1, set);
	j = 0;
	while (j < len)
	{
		res[j] = s1[i];
		j++;
		i++;
	}
	res[j] = '\0';
	return (res);
}
