/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarceli <dmarceli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:14:46 by dmarceli          #+#    #+#             */
/*   Updated: 2022/11/29 19:16:01 by dmarceli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	remove_var(t_data *data, int pos)
{
	int	i;

	i = pos - 1;
	while (i++ < data->envlen - 1)
		data->env[i] = data->env[i + 1];
	data->env[i] = 0;
	data->envlen--;
}

int	ms_unset(char *cmd, t_data *data)
{
	char	**var;
	int		pos;
	int		i;

	var = NULL;
	i = 0;
	if (!ft_strncmp(cmd, "unset\0", 6))
		printf("unset: not enough arguments\n");
	else
	{
		var = ft_split(cmd, ' ');
		while (var[++i])
		{
			pos = look_for_var_in_array(var[i], data);
			if (pos == -1)
				continue ;
			else
				remove_var(data, pos);
		}
	}
	freearray(var);
	return (1);
}