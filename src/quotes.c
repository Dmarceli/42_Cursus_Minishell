/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:03:38 by dmarceli          #+#    #+#             */
/*   Updated: 2022/12/11 19:05:35 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	checkquotation(char *input)
{
	int	i;
	int	onequote;
	int	doublequote;

	i = -1;
	onequote = 0;
	doublequote = 0;
	while (input[++i])
	{
		if (i >= 2 && input[i - 1] == '\\' && input[i - 2] != '\\')
			continue ;
		if (input[i] == '\"' && doublequote == 0 && onequote == 0)
			doublequote = 1;
		else if (input[i] == '\"' && doublequote == 1 && onequote == 0)
			doublequote = 0;
		else if (input[i] == '\'' && onequote == 0 && doublequote == 0)
			onequote = 1;
		else if (input[i] == '\'' && onequote == 1 && doublequote == 0)
			onequote = 0;
	}
	if ((onequote && !doublequote) || (!onequote && doublequote))
		return (1);
	return (0);
}

char	*removesinglequotes(char *cmd)
{
	int	j;
	int	i;

	j = 0;
	i = -1;
	while (++i < (int)ft_strlen(cmd))
	{
		if (cmd[i] == '\\')
		{
			cmd[j++] = cmd[i++];
			cmd[j++] = cmd[i];
			if (cmd[i] == '\0')
				break ;
		}
		else if (cmd[i] != '\'')
			cmd[j++] = cmd[i];
	}
	cmd[j] = '\0';
	return (cmd);
}

char	*removedoublequotes(char *cmd)
{
	int	j;
	int	i;

	j = 0;
	i = -1;
	while (++i < (int)ft_strlen(cmd))
	{
		if (cmd[i] == '\\')
		{
			cmd[j++] = cmd[i++];
			cmd[j++] = cmd[i];
			if (cmd[i] == '\0')
				break ;
		}
		else if (cmd[i] != '"')
			cmd[j++] = cmd[i];
	}
	cmd[j] = '\0';
	return (cmd);
}

char	*removequotes(char *cmd)
{
	if (ft_strchr(cmd, '\"'))
		return (removedoublequotes(cmd));
	else if (ft_strchr(cmd, '\''))
		return (removesinglequotes(cmd));
	else
		return (cmd);
}
