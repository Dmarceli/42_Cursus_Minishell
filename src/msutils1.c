/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msutils1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:16:48 by dmarceli          #+#    #+#             */
/*   Updated: 2022/12/14 20:29:27 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	big_len(char **str)
{
	int	counter;

	counter = 0;
	while (str[counter] != NULL)
		counter++;
	return (counter);
}

char	*no_var_to_expand(char **j, int i, char *value)
{
	free(j[i]);
	j[i] = ft_strdup("");
	value = join_strs(j, " ", -1);
	freearray(j);
	return (value);
}

int	output_util(char *cmd, int outs, int counter)
{
	char	*filename;
	int		fd;

	if (cmd[counter + 1] == '>')
	{
		counter++;
		filename = get_outfilename(cmd, counter + 1);
		fd = open(filename, O_RDWR | O_APPEND | O_CREAT, 0666);
	}
	else
	{
		filename = get_outfilename(cmd, counter + 1);
		fd = open(filename, O_RDWR | O_TRUNC | O_CREAT, 0666);
	}
	if (outs == 1)
	{
		free(filename);
		return (fd);
	}
	free(filename);
	close(fd);
	return (counter * -1);
}

int	input_util(char *cmd, int ins, int counter)
{
	char	*filename;
	int		fd;

	if (cmd[counter + 1] == '<' && *ft_strrchr(cmd, '<') == cmd[counter + 1])
	{
		filename = get_outfilename(cmd, counter + 2);
		fd = heredoc(filename);
		ins = 1;
	}
	else
	{
		filename = get_outfilename(cmd, counter + 1);
		fd = open(filename, O_RDONLY);
		if (fd == -1)
			counter = -1;
	}
	if (ins == 1)
	{
		free(filename);
		return (fd);
	}
	free(filename);
	close(fd);
	return (counter + 1);
}

char	*trim_util(char *old)
{
	char	*trim;
	char	*tmp;
	char	*safe;

	if (ft_strchr("<>", old[0]))
	{
		trim = ft_substr(old, 1 + trimmer(old, 1), ft_strlen(old));
	}
	else
	{
		safe = ft_substr(old, 0, special_index(old));
		tmp = ft_substr(old, (trimmer(old, special_index(old))
					+ special_index(old)), ft_strlen(old));
		trim = ft_strjoin(safe, tmp);
		free(safe);
		free(tmp);
	}
	return (trim);
}
