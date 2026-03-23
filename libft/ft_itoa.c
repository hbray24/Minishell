/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:42:57 by asauvage          #+#    #+#             */
/*   Updated: 2025/12/02 14:08:21 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	calc_len(int n)
{
	int		count;
	long	nb;

	nb = n;
	count = 1;
	if (nb == -2147483648)
		return (11);
	if (nb < 0)
	{
		count++;
		nb = nb * -1;
	}
	while (nb > 9)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		i;
	long	nb;

	i = calc_len(n);
	nb = n;
	res = malloc((i + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	res[i] = 0;
	if (nb < 0)
	{
		res[0] = '-';
		nb = nb * -1;
	}
	i--;
	while (nb > 9)
	{
		res[i] = nb % 10 + '0';
		nb = nb / 10;
		i--;
	}
	res[i] = nb % 10 + '0';
	return (res);
}
