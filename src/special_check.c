/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:18:43 by dhomem-d          #+#    #+#             */
/*   Updated: 2022/12/11 18:01:38 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	check_special(char *input, char chr)
{
	int	counter;

	counter = 0;
	while (input[counter])
	{
		if (input[counter] == chr)
		{
			if (special_quote(input, counter) == 0)
				return (1);
		}
		counter++;
	}
	return (0);
}

int	special_quote(char *input, int index)
{
	int	d_q;
	int	s_q;
	int	counter;

	if (index == -1)
		return (0);
	d_q = 0;
	s_q = 0;
	counter = index;
	while (counter > 0)
	{
		if (input[counter] == '\"')
			d_q += 1;
		else if (input[counter] == '\'')
			s_q += 1;
		counter -= 1;
	}
	if (d_q % 2 == 0 && s_q % 2 == 0)
		return (0);
	return (1);
}

int	give_inputfd(char *input)
{
	char	*filename;
	char	*tmp;
	int		fd;

	tmp = ft_strrchr(input, '<');
	filename = ft_strtrim(tmp, "< ");
	fd = open(filename, O_RDONLY);
	return (fd);
}
