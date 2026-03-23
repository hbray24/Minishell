/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:15:02 by asauvage          #+#    #+#             */
/*   Updated: 2025/12/02 14:05:42 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_b(long nb, char *base, int *count)
{
	if (nb < 0)
	{
		ft_putchar('-', count);
		nb = nb * -1;
	}
	if (nb > (long)ft_strlen(base) - 1)
	{
		ft_putnbr_b(nb / ft_strlen(base), base, count);
		ft_putnbr_b(nb % ft_strlen(base), base, count);
	}
	if (nb < (long)ft_strlen(base))
		ft_putchar(base[nb], count);
}
