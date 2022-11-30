/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msexit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:57:20 by dmarceli          #+#    #+#             */
/*   Updated: 2022/11/30 18:03:21 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	numeric_exit(char **value, t_data *data)
{
	printf("exit: %s:numeric argument required\n", value[1]);
	freearray(value);
	freearray(data->env);
	exit(255);
}

int	ft_exit(char *cmd, t_data *data)
{
	int		exit_status;
	char	**value;

	if (ft_strchr(cmd, ' '))
	{
		value = ft_split(cmd, ' ');
		exit_status = ft_atoi(value[1]);
		if (value[2])
			return (printf("exit: too many arguments"));
		else if (!is_numeric(value[1]))
			numeric_exit(value, data);
		else
		{
			freearray(value);
			freearray(data->env);
			exit(exit_status);
		}
	}
	else
	{
		freearray(data->env);
		exit(data->lastexec);
	}
	return (0);
}