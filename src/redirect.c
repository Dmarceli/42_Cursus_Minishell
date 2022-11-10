/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:21:08 by dhomem-d          #+#    #+#             */
/*   Updated: 2022/11/10 18:57:54 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	check_redirect(char *cmd)
{
	if (special_quote(cmd, ft_index(cmd, '>')))
		return (overwrite(cmd));
	else
		return (STDOUT_FILENO);
}

int	overwrite(char *cmd)
{
	char	*filename;
	char	*tmp;
	int		fd;

	tmp = ft_substr(cmd, ft_index(cmd, '>') + 1, ft_strlen(cmd));
	filename = ft_strtrim(tmp, " ");
	free(tmp);
	fd = open(filename, O_RDWR | O_TRUNC | O_CREAT, 0666);
	free(filename);
	return fd;
}

int	ft_index(char *str, char ch)
{
	int	counter;

	counter = 0;
	while (str[counter])
	{
		if (str[counter] == ch)
			return (counter);
		counter++;
	}
	return -1;
}

char	*return_trim(char *bush)
{
	char	*trim;

	trim = ft_substr(bush, 0, ft_index(bush, '>'));
	free(bush);
	return (trim);
}