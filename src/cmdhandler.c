/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdhandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:35:28 by dmarceli          #+#    #+#             */
/*   Updated: 2022/12/10 01:57:23 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	is_builtin(char *value, t_data *data)
{
	if (!check_emptyprompt(value))
		return (printf("%s: command not found\n", value));
	if (!value)
		return (0);
	else if (!(ft_strncmp(value, "echo ", 5)))
		return (data->lastexec = echo(removequotes(value)));
	else if (!(ft_strncmp(value, "cd ", 3)))
		return (data->lastexec = ms_cd(removequotes(value), data));
	else if (!(ft_strncmp(value, "pwd ", 4)))
		return (data->lastexec = ms_pwd(removequotes(value)));
	else if (!(ft_strncmp(value, "export", 6)))
		return (data->lastexec = ms_export(removequotes(value), data));
	else if (!(ft_strncmp(value, "unset ", 6)))
		return (data->lastexec = ms_unset(removequotes(value), data));
	else if (!(ft_strncmp(value, "env", 3)))
		return (env(data));
	else if (!(ft_strncmp(value, "exit", 4)))
		return (ft_exit(removequotes(value), data));
	else
		return (executecmd(removequotes(value), data));
}

int	is_parent(char *cmd, t_data *data)
{
	char	*value;

	value = ft_strtrim(cmd, " ");
	if (!(ft_strncmp(value, "cd ", 3)))
		data->lastexec = ms_cd(removequotes(value), data);
	else if (!(ft_strncmp(value, "export", 6)))
		data->lastexec = ms_export(removequotes(value), data);
	else if (!(ft_strncmp(value, "unset ", 6)))
		data->lastexec = ms_unset(removequotes(value), data);
	else if (!(ft_strncmp(value, "exit", 4)))
		ft_exit(removequotes(value), data);
	else
	{
		free(value);
		return (0);
	}
	free(value);
	return (1);
}
