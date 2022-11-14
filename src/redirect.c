/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:21:08 by dhomem-d          #+#    #+#             */
/*   Updated: 2022/11/14 20:09:51 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

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

int	input_red(char *cmd)
{
	int		fd;
	char	*filename;

	filename = get_infilename(cmd);
	fd = open(filename, O_RDONLY);
	free(filename);
	return (fd);
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
	while(tmp[sub_counter] == ' ')
		sub_counter++;
	while (ft_strchr("<> \0", tmp[sub_counter]) == NULL)
	{
		filename[counter] = tmp[sub_counter];
		counter++;
		sub_counter++;
	}
	filename[counter] = '\0';
	//free(tmp);
	return (filename);
}

void	redirect(char *cmd, t_data *data)
{
	int	fd_in;
	int	fd_out;

	if (check_special(cmd, '<'))
	{
		fd_in = input_red(cmd);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (check_special(cmd, '>'))
	{
		fd_out = output(cmd);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	cmd = return_trim(cmd);
	is_builtin(cmd, data);
	exit(0);
}