/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:50:07 by dhomem-d          #+#    #+#             */
/*   Updated: 2022/12/14 19:33:33 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	count_redir(char *cmd, char red)
{
	int	counter;
	int	red_counter;

	counter = 0;
	red_counter = 0;
	while (cmd[counter])
	{
		if (cmd[counter] == red && special_quote(cmd, counter) == 0)
		{
			red_counter++;
			counter++;
			if (cmd[counter] == red)
				counter++;
		}
		else
			counter++;
	}
	return (red_counter);
}

int	special_index(char *str)
{
	int	out;
	int	in;

	out = ft_index(str, '>');
	in = ft_index(str, '<');
	if (out == -1)
		return (in);
	else if (in == -1)
		return (out);
	else if (out < in)
		return (out);
	else
		return (in);
}

int	trimmer(char *bush, int counter)
{
	int	size;

	size = 0;
	while (ft_strchr("<> ", bush[counter]))
	{
		counter++;
		size++;
	}
	while (ft_strchr(">< ", bush[counter]) == NULL)
	{
		counter++;
		size++;
	}
	return (size);
}

char	*return_trim(char *bush)
{
	char	*trim;
	char	*old;

	old = ft_strdup(bush);
	trim = ft_strdup(bush);
	while (ft_strchr(trim, '<') || ft_strchr(trim, '>'))
	{
		free(trim);
		trim = trim_util(old);
		free(old);
		old = strdup(trim);
	}
	free(old);
	free(bush);
	return (trim);
}

char	*get_infilename(char *cmd)
{
	char	*tmp;
	char	*filename;
	int		counter;
	int		sub_counter;

	tmp = ft_strrchr(cmd, '<');
	counter = 0;
	sub_counter = 0;
	filename = ft_calloc(ft_strlen(cmd), sizeof(char));
	sub_counter++;
	while (tmp[sub_counter] == ' ')
		sub_counter++;
	while (ft_strchr("<> \0", tmp[sub_counter]) == NULL)
	{
		filename[counter] = tmp[sub_counter];
		counter++;
		sub_counter++;
	}
	filename[counter] = '\0';
	return (filename);
}
