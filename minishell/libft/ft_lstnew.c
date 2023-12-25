/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beeren <beeren@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:33:36 by bgursoy           #+#    #+#             */
/*   Updated: 2023/12/20 15:28:34 by beeren           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*ptr;

	ptr = (t_list *)malloc(sizeof(t_list));
	if (!ptr)
		return (0);
	ptr->next = NULL;
	ptr->content = content;
	return (ptr);
}
