/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:56:31 by dmarceli          #+#    #+#             */
/*   Updated: 2022/12/11 18:17:30 by dhomem-d         ###   ########.fr       */
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
		input = readline(CYAN"minishell> "BLANK);
		if (!input && write(0, "\n", 1))
			ft_exit("exit", &data);
		ignore_signal_i();
		data.lastexec = g_exitvalue;
		minishellparser(input, &data);
		ignore_signal();
	}
	return (g_exitvalue);
}
