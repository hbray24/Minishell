/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:00:08 by asauvage          #+#    #+#             */
/*   Updated: 2025/12/02 14:07:25 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	verif_malloc(char const *s, unsigned int start, size_t len)
{
	size_t	len_f;

	if (start > 4294967294)
		return (0);
	len_f = ft_strlen(&s[start]);
	if (len_f > len)
		len_f = len;
	if (start > ft_strlen(s))
		len_f = 0;
	return (len_f);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	len_f;

	len_f = verif_malloc(s, start, len);
	res = malloc((len_f + 1) * sizeof(char));
	if (res == NULL)
		return (0);
	res[0] = '\0';
	if (start > ft_strlen(s))
		return (res);
	i = 0;
	while (i < len && s[start] != '\0')
		res[i++] = s[start++];
	res[i] = '\0';
	return (res);
}
