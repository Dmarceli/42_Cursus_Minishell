/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msutils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarceli <dmarceli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:01:51 by dmarceli          #+#    #+#             */
/*   Updated: 2022/11/29 19:02:58 by dmarceli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	freearray(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
	{
		if (arr[i])
			free(arr[i]);
	}
	free(arr);
	arr = NULL;
}

char	*join_strs(char **str_chunks, char *sep, int limiter)
{
	int		k;
	char	*complete_str;

	k = -1;
	complete_str = 0;
	while (str_chunks[++k] && (k < limiter || limiter < 0))
	{
		if (!complete_str)
			complete_str = ft_strjoin(sep, str_chunks[k]);
		else
		{
			complete_str = ft_strjoin(complete_str, sep);
			complete_str = ft_strjoin(complete_str, str_chunks[k]);
		}
	}
	if (complete_str)
		return (ft_strjoin(complete_str, sep));
	return (complete_str);
}

int	look_for_var_in_array(char *cmd, t_data *data)
{
	int		i;
	size_t	len;

	i = -1;
	len = ft_strlen(cmd);
	while (data->env[++i])
	{
		if (!ft_strncmp(cmd, data->env[i], len))
			return (i);
	}
	return (-1);
}

int	is_numeric(char *value)
{
	int	j;

	j = ft_strlen(value);
	while (j--)
	{
		if (value[j] >= '0' && value[j] <= '9')
			continue ;
		else
			return (0);
	}
	return (1);
}

char	*no_var_to_expand(char **j, int i, char *value)
{
	free(j[i]);
	j[i] = ft_strdup("");
	value = join_strs(j, " ", -1);
	freearray(j);
	return (value);
}
