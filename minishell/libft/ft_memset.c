/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgursoy <bgursoy@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:34:31 by bgursoy           #+#    #+#             */
/*   Updated: 2023/12/20 13:34:32 by bgursoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	char	*dest;

	dest = b;
	i = 0;
	while (i < len)
	{
		dest[i] = c;
		i++;
	}
	return (b);
}
