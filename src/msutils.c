/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msutils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:01:51 by dmarceli          #+#    #+#             */
/*   Updated: 2022/12/05 17:57:47 by dhomem-d         ###   ########.fr       */
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

char	*ft_strfree_join(char **s1, char *s2)
{
	char	*result;

	result = ft_strjoin(*s1, s2);
	free(*s1);
	return (result);
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
			complete_str = ft_strfree_join(&complete_str, sep);
			complete_str = ft_strfree_join(&complete_str, str_chunks[k]);
		}
	}
	if (complete_str)
		return (ft_strfree_join(&complete_str, sep));
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
