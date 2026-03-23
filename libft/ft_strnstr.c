/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:18:10 by asauvage          #+#    #+#             */
/*   Updated: 2025/12/02 14:15:08 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	char	*tmp_s1;
	char	*tmp_s2;

	tmp_s1 = (char *)s1;
	tmp_s2 = (char *)s2;
	i = 0;
	if (tmp_s1[0] == '\0' || len == 0)
	{
		if (ft_strlen(tmp_s2) != 0)
			return (0);
		return (tmp_s1);
	}
	while (i < len)
	{
		if ((i + ft_strlen(tmp_s2) <= len) && ft_strncmp(&tmp_s1[i], tmp_s2,
				ft_strlen(tmp_s2)) == 0)
			return (&tmp_s1[i]);
		i++;
	}
	return (0);
}
