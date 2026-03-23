/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_address.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 14:23:40 by asauvage          #+#    #+#             */
/*   Updated: 2025/12/02 14:05:21 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_address(unsigned long nb, char *base, int *count)
{
	if (nb > (unsigned long)ft_strlen(base) - 1)
	{
		ft_putnbr_address(nb / ft_strlen(base), base, count);
		ft_putnbr_address(nb % ft_strlen(base), base, count);
	}
	if (nb < (unsigned long)ft_strlen(base))
		ft_putchar(base[nb], count);
}
