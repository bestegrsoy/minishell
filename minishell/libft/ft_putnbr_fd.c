/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgursoy <bgursoy@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:34:46 by bgursoy           #+#    #+#             */
/*   Updated: 2023/12/20 13:34:47 by bgursoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nb = (nb * -1);
	}
	if (nb < 10)
		ft_putchar_fd(nb + 48, fd);
	if (nb > 9)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putnbr_fd(nb % 10, fd);
	}
}
