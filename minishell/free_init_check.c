/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_init_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgursoy <bgursoy@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:19:54 by bgursoy           #+#    #+#             */
/*   Updated: 2023/12/21 16:48:24 by bgursoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	free_init_check(t_mini *mini)
{
	if (mini->env)
		free_(mini);
	if (mini->lex_list)
		free(mini->lex_list);
	if (mini->lex_list->lex)
		free(mini->lex_list->lex);
	if (mini)
		free(mini);
}
