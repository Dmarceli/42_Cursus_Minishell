/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 01:18:18 by dhomem-d          #+#    #+#             */
/*   Updated: 2022/12/27 22:07:06 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*norm_findvar(char *cmd)
{
	char	*var;

	if (ft_strchr(cmd, '\"'))
		var = ft_strtrim(cmd, "\"");
	else
		var = ft_substr(cmd, 1, (ft_strlen(cmd)));
	return (var);
}

char	*justthevar(char *str)
{
	int		len;
	char	*ret;
	int		i;

	len = 0;
	i = 0;
	while (str[len] != '=')
		len++;
	ret = malloc(sizeof(char) * len + 1);
	ret[len] = '\0';
	while (i < len)
	{
		ret[i] = str[i];
		i++;
	}
	return (ret);
}

void	sortarray(char **strings, int len)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strcmp(strings[i], strings[j]) > 0)
			{
				temp = strings[i];
				strings[i] = strings[j];
				strings[j] = temp;
			}
			j++;
		}
	i++;
	}
}
