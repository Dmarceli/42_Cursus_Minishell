/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:50:07 by dhomem-d          #+#    #+#             */
/*   Updated: 2022/11/14 18:25:34 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	count_output(char *cmd)
{
	int	counter;
	int	out_counter;

	counter = 0;
	out_counter = 0;
	while (cmd[counter])
	{
		if (cmd[counter] == '>' && special_quote(cmd, counter) == 0)
		{
			out_counter++;
			counter++;
			if (cmd[counter] == '>')
				counter++;
		}
		else
			counter++;
	}
	return (out_counter);
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