/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguinot <cguinot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:38:11 by cguinot           #+#    #+#             */
/*   Updated: 2024/11/16 17:49:35 by cguinot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *s)
{
	int	len;

	len = 0;
	if (!s)
		return (write(1, "(null)", 6));
	while (*s)
		len += ft_putchar(*s++);
	return (len);
}

int	ft_putptr(void *ptr)
{
	unsigned long	address;
	int				len;

	if (!ptr)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	address = (unsigned long)ptr;
	len = 2;
	write(1, "0x", 2);
	len += ft_putnbrbase(address, "0123456789abcdef");
	return (len);
}
