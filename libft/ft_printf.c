/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auxence <auxence@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:58:14 by asauvage          #+#    #+#             */
/*   Updated: 2025/12/19 17:57:27 by auxence          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	verif_print(char c, va_list *ap, int *count)
{
	if (c == 'c')
		ft_putchar(va_arg(*ap, int), count);
	else if (c == 's')
		ft_putstr(va_arg(*ap, char *), count);
	else if (c == 'p')
		ft_address(va_arg(*ap, void *), count);
	else if (c == 'd' || c == 'i')
		ft_putnbr_b(va_arg(*ap, int), "0123456789", count);
	else if (c == 'u')
		ft_putnbr_b(va_arg(*ap, unsigned int), "0123456789", count);
	else if (c == 'x')
		ft_putnbr_b(va_arg(*ap, unsigned int), "0123456789abcdef", count);
	else if (c == 'X')
		ft_putnbr_b(va_arg(*ap, unsigned int), "0123456789ABCDEF", count);
	else if (c == '%')
		ft_putchar('%', count);
}

int	ft_printf(const char *format, ...)
{
	int		count;
	int		i;
	va_list	ap;

	va_start(ap, format);
	i = 0;
	count = 0;
	if (format == NULL)
		return (-1);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
			verif_print(format[++i], &ap, &count);
		else
			ft_putchar(format[i], &count);
		i++;
	}
	va_end(ap);
	return (count);
}
