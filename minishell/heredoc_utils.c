/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgursoy <bgursoy@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:16:12 by bgursoy           #+#    #+#             */
/*   Updated: 2023/12/21 16:48:20 by bgursoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <sys/ioctl.h>
#include <unistd.h>

void	killer(int sig)
{
	(void)sig;
	g_heredoc_sig = -3;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	set_heredoc(int sig)
{
	(void)sig;
	g_heredoc_sig = -10;
}
