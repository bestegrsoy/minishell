/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgursoy <bgursoy@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:18:55 by bgursoy           #+#    #+#             */
/*   Updated: 2023/12/21 16:49:09 by bgursoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

int	env_get(char **env, t_mini **mini)
{
	t_env	*key_v;
	char	**str;

	free((*mini)->env);
	(*mini)->env = NULL;
	while (*env)
	{
		key_v = malloc(sizeof(t_env));
		if (!key_v)
			return (ft_putstr_fd(A_ERR, 2), 1);
		str = ft_split(*env, '=');
		key_v->key = ft_strdup(str[0]);
		key_v->value = ft_strdup(str[1]);
		ft_lstadd_back(&(*mini)->env, ft_lstnew(key_v));
		free_str(str);
		env++;
	}
	return (0);
}
