/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarceli <dmarceli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:21:08 by dhomem-d          #+#    #+#             */
/*   Updated: 2022/11/23 15:46:49 by dmarceli         ###   ########.fr       */
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
	if (*(ft_strrchr(cmd, '<') - 1) == '<')
		fd = heredoc(filename);
	else
		fd = open(filename, O_RDONLY);
	free(filename);
	return (fd);
}

int	heredoc(char *eof)
{
	char	*content;
	int		tmp_fd;
	int		fd_in;

	tmp_fd = open("./.tmp/tmpfile.txt", O_TRUNC | O_CREAT | O_WRONLY, 0666);
	write(1, "> ", 2);
	content = get_next_line(STDIN_FILENO);
	while(1)
	{
		if (ft_strncmp(content, eof, ft_strlen(content) - 1) == 0)
			break;
		write(tmp_fd, content, ft_strlen(content));
		free(content);
		write(1, "> ", 2);
		content = get_next_line(STDIN_FILENO);
	}
	free(content);
	close(tmp_fd);
	fd_in = open("./.tmp/tmpfile.txt", O_RDONLY, 0777);
	return fd_in;
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