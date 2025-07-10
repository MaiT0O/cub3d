/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_type2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguinot <cguinot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:51:33 by cguinot           #+#    #+#             */
/*   Updated: 2024/11/16 17:35:03 by cguinot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int n)
{
	char	c;
	int		count;

	count = 0;
	if (n == -2147483648)
		return (write(1, "-2147483648", 11));
	if (n < 0)
	{
		count += ft_putchar('-');
		n = -n;
	}
	if (n > 9)
		count += ft_putnbr(n / 10);
	c = (n % 10) + '0';
	return (count + ft_putchar(c));
}

int	ft_putnbr_unsigned(unsigned int n)
{
	char	c;
	int		count;

	count = 0;
	if (n > 9)
		count += ft_putnbr_unsigned(n / 10);
	c = (n % 10) + '0';
	return (count + ft_putchar(c));
}

int	ft_putnbrbase(unsigned long n, char *base)
{
	int		count;

	count = 0;
	if (n >= 16)
		count += ft_putnbrbase(n / 16, base);
	return (count + ft_putchar(base[n % 16]));
}
