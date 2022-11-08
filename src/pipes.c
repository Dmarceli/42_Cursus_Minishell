/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 21:36:51 by dhomem-d          #+#    #+#             */
/*   Updated: 2022/11/08 21:49:34 by dhomem-d         ###   ########.fr       */
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
			multiple_child(cmds, data, counter);
		close(data->fd[1]);
		waitpid(data->pid, NULL, 0);
		data->pipe_fd = data->fd[0];
		counter++;
	}
	return ;
}

void multiple_child(char **cmds, t_data *data, int counter)
{
	int	fd_red;

	if (counter == 0)
		close(data->fd[0]);
	else if (counter > 0)
	{
		dup2(data->pipe_fd, STDIN_FILENO);
		close(data->pipe_fd);
	}
	if (counter != big_len(cmds) - 1)
		dup2(data->fd[1], STDOUT_FILENO);
	if (counter == big_len(cmds) - 1)
	{
		fd_red = check_redirect(cmds[counter]);
		if (fd_red != STDOUT_FILENO)
		{
			dup2(fd_red, STDOUT_FILENO);
			close(fd_red);
			cmds[counter] = return_trim(cmds[counter]);
		}
	}
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