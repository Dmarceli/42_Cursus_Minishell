/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duartebaeta <duartebaeta@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 21:36:51 by dhomem-d          #+#    #+#             */
/*   Updated: 2022/11/21 20:15:30 by duartebaeta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	handle_pipes(char **cmds, t_data *data)
{
	int	counter;

	counter = 0;
	while (cmds[counter])
	{
		if (pipe(data->fd) == -1)
			return ;
		data->pid = fork();
		if (data->pid < 0)
			return ;
		if (data->pid == 0)
			child_process(cmds, data, counter);
		close(data->fd[1]);
		waitpid(data->pid, NULL, 0);
		data->pipe_fd = data->fd[0];
		counter++;
	}
	return ;
}

void child_process(char **cmds, t_data *data, int counter)
{
	int	fd_in;
	int	fd_out;

	if (check_special(cmds[counter], '<') == 0)
	{
		if (counter == 0)
			close(data->fd[0]);
		else if (counter > 0)
		{
			dup2(data->pipe_fd, STDIN_FILENO);
			close(data->pipe_fd);
		}
	}
	else
	{
		if (counter == 0)
			close(data->fd[0]);
		else if (counter > 0)
			close(data->pipe_fd);
		fd_in = input_red(cmds[counter]);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (check_special(cmds[counter], '>') == 0)
	{
		if (counter != big_len(cmds) - 1)
			dup2(data->fd[1], STDOUT_FILENO);
	}
	else
	{
		fd_out = output(cmds[counter]);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	if (check_special(cmds[counter], '>') || check_special(cmds[counter], '<'))
		cmds[counter] = return_trim(cmds[counter]);
	is_builtin(cmds[counter], data);
	exit(0);
}

int	big_len(char **str)
{
	int	counter;

	counter = 0;
	while (str[counter])
		counter++;
	return (counter);
}