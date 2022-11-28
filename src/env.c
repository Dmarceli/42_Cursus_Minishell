/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarceli <dmarceli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 17:44:31 by dmarceli          #+#    #+#             */
/*   Updated: 2022/11/28 17:44:53 by dmarceli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	initenv(char **envs, t_data *data)
{
	int	i;

	i = 0;
	while (envs[i])
		i++;
	data->envlen = i;
	data->env = (char **)malloc(sizeof(char *) * (i + 10));
	i = 0;
	while (i < data->envlen)
	{
		data->env[i] = ft_strdup(envs[i]);
		i++;
	}
	data->env[i] = 0;
	data->lastexec = 0;
}

int	env(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->envlen)
		printf("%s\n", data->env[i]);
	return (1);
}