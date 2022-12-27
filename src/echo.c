/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 17:33:02 by dmarceli          #+#    #+#             */
/*   Updated: 2022/12/27 22:00:01 by dani             ###   ########.fr       */
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
			if (ft_strcmp("-n", value[i]))
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

	i = 1;
	if (cmd[0] == '-' && cmd[1] == 'n' )
	{	
		while (cmd[i])
		{
			if (cmd[i] != 'n' && cmd[i] != '\0')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

char	*remove_escape(char *cmd)
{
	int		counter;
	int		ret_counter;
	char	*ret;

	if (!ft_strchr(cmd, '\\'))
		return (cmd);
	counter = -1;
	ret_counter = -1;
	ret = malloc(sizeof(char) * ft_strlen(cmd));
	while (cmd[++counter])
	{
		if (cmd[counter] == '\\' && cmd[counter - 1] != '\\')
			continue ;
		ret[++ret_counter] = cmd[counter];
	}
	ret[ret_counter + 1] = '\0';
	free(cmd);
	return (ret);
}

int	echo(char *cmd)
{
	int		is_n;
	char	**value;
	char	*tmp;

	tmp = ft_strtrim(cmd, " ");
	tmp = remove_escape(tmp);
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
