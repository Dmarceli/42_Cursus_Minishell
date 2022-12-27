/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:56:31 by dmarceli          #+#    #+#             */
/*   Updated: 2022/12/26 17:58:21 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int		g_exitvalue;

int	main(int ac, char **av, char **envs)
{	
	t_data	data;
	char	*input;

	(void)ac;
	(void)av;
	initenv(envs, &data);
	ignore_signal();
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			ft_exit("exit", &data);
		ignore_signal_i();
		data.lastexec = g_exitvalue;
		minishellparser(input, &data);
		ignore_signal();
	}
	return (g_exitvalue);
}
