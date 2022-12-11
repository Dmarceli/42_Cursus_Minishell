/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msparser_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 01:23:31 by dhomem-d          #+#    #+#             */
/*   Updated: 2022/12/11 18:01:56 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	else
		return (0);
}

int	check_emptyprompt(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (is_space(cmd[i]))
			i++;
		else
			return (1);
	}
	return (0);
}

int	check_inquotes(char *cmd)
{
	int		ret;
	int		len;
	char	*tmp;

	tmp = ft_strtrim(cmd, " ");
	len = ft_strlen(tmp) - 1;
	ret = norm_inquotes(tmp, len);
	free(tmp);
	return (ret);
}

int	norm_inquotes(char *tmp, int len)
{
	int		counter;
	char	quote;

	counter = 1;
	quote = tmp[0];
	if (quote == '\"' || quote == '\'')
	{
		while (tmp[counter])
		{
			if (tmp[counter] == quote && counter == len)
				break ;
			else if (tmp[counter] == quote && tmp[counter - 1] != '\\')
				return (0);
			counter++;
		}
		return (1);
	}
	else
		return (0);
}
