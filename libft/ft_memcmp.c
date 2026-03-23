/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 17:24:46 by asauvage          #+#    #+#             */
/*   Updated: 2025/12/02 14:08:44 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*tmp_s1;
	unsigned char	*tmp_s2;
	size_t			i;
	int				res;

	tmp_s1 = (unsigned char *)s1;
	tmp_s2 = (unsigned char *)s2;
	i = 0;
	res = 0;
	if (n == 0)
		return (0);
	while (tmp_s1[res] == tmp_s2[res] && i < n - 1)
	{
		i++;
		res++;
	}
	res = tmp_s1[res] - tmp_s2[res];
	return (res);
}
