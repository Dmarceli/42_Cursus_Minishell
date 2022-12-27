/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:21:08 by dhomem-d          #+#    #+#             */
/*   Updated: 2022/12/27 22:02:03 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	output(char *cmd)
{
	int		fd;
	int		outs;
	int		counter;

	outs = count_redir(cmd, '>');
	counter = 0;
	while (outs && cmd[counter] != 0)
	{
		if (cmd[counter] != '>')
			counter++;
		else if (special_quote(cmd, counter) == 0)
		{
			fd = output_util(cmd, outs, counter);
			if (fd <= 0)
				counter = (fd * -1) + 1;
			else
				return (fd);
			outs--;
		}
		else
			counter++;
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
	int	fd;
	int	counter;
	int	ins;

	counter = 0;
	fd = -1;
	ins = count_redir(cmd, '<');
	while (ins && cmd[counter] != '\0')
	{
		if (cmd[counter] != '<')
			counter++;
		else
		{
			if (ins == 1)
				fd = input_util(cmd, ins, counter);
			else
				counter = input_util(cmd, ins, counter);
			if (counter < 0)
				break ;
			ins--;
		}
	}
	if (fd == -1 || counter == -1)
		printf("%s\n", strerror(errno));
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
		if (ft_strncmp(content, eof, ft_strlen(content) - 1) == 0
			&& ft_strlen(content) > 1)
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
			exit(g_exitvalue);
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
	exit(g_exitvalue);
}
