/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 17:55:45 by asauvage          #+#    #+#             */
/*   Updated: 2025/12/02 14:08:06 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	tot;

	tot = nmemb * size;
	if (nmemb > 65534 && size > 65534)
		return (NULL);
	ptr = malloc(tot);
	if (ptr == NULL)
		return (0);
	ft_bzero(ptr, tot);
	return (ptr);
}
