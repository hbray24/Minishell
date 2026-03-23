/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:17:54 by asauvage          #+#    #+#             */
/*   Updated: 2025/12/02 14:09:37 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	len_tot;

	len_tot = ft_strlen(s1) + ft_strlen(s2) + 1;
	res = malloc((len_tot) * sizeof(char));
	if (res == NULL)
		return (0);
	res[0] = '\0';
	ft_strlcat(res, s1, ft_strlen(s1) + 1);
	ft_strlcat(res, s2, len_tot);
	return (res);
}
