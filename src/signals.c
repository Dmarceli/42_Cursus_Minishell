/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:13:29 by dmarceli          #+#    #+#             */
/*   Updated: 2022/12/11 18:18:18 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	sighandler_i(int sig)
{
	if (sig == SIGINT)
	{
		write(0, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		g_exitvalue = 130;
	}
	if (sig == SIGQUIT)
	{
		write(0, "Quit (core dumped)\n", 20);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	ignore_signal_i(void)
{
	signal(SIGQUIT, sighandler_i);
	signal(SIGINT, sighandler_i);
}

void	sighandler(int sig)
{
	if (sig == SIGINT)
	{
		write(0, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exitvalue = 130;
	}
}

void	ignore_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sighandler);
}
