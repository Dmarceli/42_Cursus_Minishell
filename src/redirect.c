/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:21:08 by dhomem-d          #+#    #+#             */
/*   Updated: 2022/12/11 19:28:35 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	output(char *cmd)
{
	int		fd;
	int		outs;
	int		counter;

	outs = count_output(cmd);
	counter = 0;
	while (outs && cmd[counter] != 0)
	{
		if (cmd[counter] != '>')
			counter++;
		else
		{
			fd = output_util(cmd, outs, counter);
			if (fd <= 0)
				counter = (fd * -1) + 1;
			else
				return (fd);
			outs--;
		}
	}
	return (fd);
}

char	*get_outfilename(char *cmd, int counter)
{
	char	*filename;
	int		subcounter;

	subcounter = 0;
	filename = ft_calloc(ft_strlen(cmd), sizeof(char));
	while (cmd[counter] == ' ')
		counter++;
	while (ft_strchr(">< ", cmd[counter]) == NULL && cmd[counter] != '\0')
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
	if (fd == -1)
		printf("%s\n", strerror(errno));
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
	while (1)
	{
		if (ft_strncmp(content, eof, ft_strlen(content) - 1) == 0)
			break ;
		write(tmp_fd, content, ft_strlen(content));
		free(content);
		write(1, "> ", 2);
		content = get_next_line(STDIN_FILENO);
	}
	free(content);
	close(tmp_fd);
	fd_in = open("./.tmp/tmpfile.txt", O_RDONLY, 0777);
	return (fd_in);
}

void	redirect(char *cmd, t_data *data)
{
	int	fd_in;
	int	fd_out;

	if (check_special(cmd, '<'))
	{
		fd_in = input_red(cmd);
		if (fd_in <= -1)
		{
			g_exitvalue = errno;
			exit(errno);
		}
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
