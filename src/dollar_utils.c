/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 01:18:18 by dhomem-d          #+#    #+#             */
/*   Updated: 2022/12/11 18:02:03 by dhomem-d         ###   ########.fr       */
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
