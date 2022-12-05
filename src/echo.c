/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarceli <dmarceli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 17:33:02 by dmarceli          #+#    #+#             */
/*   Updated: 2022/12/05 14:47:39 by dmarceli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	exec_echo(char **value, int is_n)
{
	int	i;

	if (is_n)
	{
		i = 1;
		while (value[++i])
			printf("%s ", value[i]);
		freearray(value);
		return (0);
	}
	else if (!is_n)
	{
		i = 0;
		while (value[++i])
			printf("%s ", value[i]);
		printf("\n");
		freearray(value);
		return (0);
	}
	else
		freearray(value);
	return (2);
}

int	checkechoflag(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '-' && cmd[i + 1] == 'n' )
			return (1);
		i++;
	}
	return (0);
}

int	echo(char *cmd)
{
	int		is_n;
	char	**value;
	char	*tmp;

	tmp = ft_strtrim(cmd, " ");
	if (ft_strchr(tmp, ' '))
		value = ft_split(tmp, ' ');
	else
	{
		printf("\n");
		return (0);
	}
	free(tmp);
	is_n = checkechoflag(value[1]);
	return (exec_echo(value, is_n));
}
