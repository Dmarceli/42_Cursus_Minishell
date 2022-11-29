/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarceli <dmarceli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:56:31 by dmarceli          #+#    #+#             */
/*   Updated: 2022/11/29 18:57:10 by dmarceli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	main(int ac, char **av, char **envs)
{	
	t_data	data;
	int		exitvalue;
	char	*input;

	(void)ac;
	(void)av;
	initenv(envs, &data);
	ignore_signal();
	while (1)
	{
		input = readline(CYAN"minishell> "BLANK);
		if (!input && write(0, "\n", 1))	
			ft_exit("", &data);
		ignore_signal_i();
		minishellparser(input, &data);
		ignore_signal();
		exitvalue = data.lastexec;
	}
	return (exitvalue);
}
