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

// int	overwrite(char *cmd)
// {
// 	char	*filename;
// 	int		fd;

// 	filename = get_filename(cmd, '>');
// 	fd = open(filename, O_RDWR | O_TRUNC | O_CREAT, 0666);
// 	free(filename);
// 	return fd;
// }

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

int	output(char *cmd)
{
	char	*filename;
	int		fd;
	int		outs;
	int		counter;

	outs = count_output(cmd);
	counter = 0;
	while(outs && cmd[counter] != 0)
	{
		if (cmd[counter] != '>')
			counter++;
		else
		{
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
			outs--;
			free(filename);
			close(fd);
			counter++;
		}
	}
	return (fd);
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
	char	*tmp;
	char	*safe;
	char	*old;

	old = ft_strdup(bush);
	trim = ft_strdup(bush);
	while (ft_strchr(trim, '<') || ft_strchr(trim, '>'))
	{
		free(trim);
		if (ft_strchr("<>", old[0]))
		{
			trim = ft_substr(old, 1 + trimmer(old, 1), ft_strlen(old));
		}
		else
		{
			safe = ft_substr(old, 0, special_index(old));
			tmp = ft_substr(old, (trimmer(old, special_index(old)) + special_index(old)), ft_strlen(old));
			trim = ft_strjoin(safe, tmp);
			free(safe);
			free(tmp);
		}
		free(old);
		old = strdup(trim);
	}
	free(old);
	free(bush);
	return (trim);
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

char	*get_outfilename(char *cmd, int counter)
{
	char	*filename;
	int		subcounter;

	subcounter = 0;
	filename = ft_calloc(ft_strlen(cmd), sizeof(char));
	while (cmd[counter] == ' ')
		counter++;
	while(ft_strchr(">< ", cmd[counter]) == NULL && cmd[counter] != '\0')
	{
		filename[subcounter] = cmd[counter];
		subcounter++;
		counter++;
	}
	filename[subcounter] = '\0';
	return (filename);
}

// char	*get_infilename(char *cmd, char chr)
// {
// 	char	*tmp;
// 	char	*filename;
// 	int		counter;

// 	tmp = ft_strrchr(cmd, chr);
// 	counter = 0;
// 	filename = ft_calloc(ft_strlen(red) * sizeof(char));
// 	*tmp++;
// 	while(*tmp == ' ')
// 		*tmp++;
// 	while (*tmp != ' ' && *tmp != '>' && *tmp != '<')
// 	{
// 		filename[counter] = *tmp;
// 		counter++;
// 		*tmp++;
// 	}
// 	filename[counter] = '\0';
// 	free(tmp);
// 	return (filename);
// }