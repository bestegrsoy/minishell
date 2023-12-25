/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgursoy <bgursoy@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:16:40 by bgursoy           #+#    #+#             */
/*   Updated: 2023/12/21 16:48:29 by bgursoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	expand_dollar_variable(t_mini *mini, t_list *lex, char **temp,
		char *before)
{
	char	*new_value;

	if (ft_isdigit((*temp)[1]))
	{
		new_value = ft_strdup(*temp + 2);
		free(lex->content);
		lex->content = ft_strjoin(before, new_value);
		free(new_value);
		*temp = ft_strchr(lex->content + ft_strlen(before), '$');
	}
	else
	{
		new_value = get_env(mini->env, *temp + 1);
		free(lex->content);
		lex->content = ft_strjoin(before, new_value);
		if ((char *)lex->content == NULL)
			lex->content = ft_strdup(before);
		free(new_value);
		*temp = ft_strchr(lex->content + ft_strlen(before), '$');
	}
}

void	expand_question_mark(t_mini *mini, t_list *lex, char **temp,
		char *before)
{
	char	*after;
	char	*back;
	char	*new_value;

	after = ft_strdup(*temp + 2);
	free(lex->content);
	new_value = ft_itoa(mini->exec_status);
	back = ft_strjoin(new_value, after);
	free(new_value);
	free(after);
	lex->content = ft_strjoin(before, back);
	free(back);
	*temp = ft_strchr(lex->content + ft_strlen(before), '$');
}

void	expander_tilde(t_mini *mini, t_list *lex)
{
	char	*content;
	char	*home;
	char	*tmp;

	home = get_env(mini->env, "HOME");
	content = (char *)lex->content;
	if (content[0] == '~')
	{
		if (content[1] == '/')
		{
			tmp = ft_strdup(content + 1);
			free(lex->content);
			lex->content = ft_strjoin(home, tmp);
			free(tmp);
		}
		else if (content[1] == '\0')
		{
			free(lex->content);
			lex->content = home;
		}
	}
	else
		free(home);
}
