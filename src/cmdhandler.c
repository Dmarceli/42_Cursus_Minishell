/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdhandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:35:28 by dmarceli          #+#    #+#             */
/*   Updated: 2022/12/16 16:23:51 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	is_builtin(char *value, t_data *data)
{
	if (ft_strchr(value, ' ') && check_inquotes(value))
		return (executecmd(value, data));
	if (!check_emptyprompt(value))
		return (printf("%s: command not found\n", value));
	if (!value)
		return (0);
	else if (!(ft_strncmp(value, "echo ", 5)))
		return (g_exitvalue = echo(removequotes(value)));
	else if (!(ft_strncmp(value, "cd ", 3)))
		return (g_exitvalue = ms_cd(removequotes(value), data));
	else if (!(ft_strncmp(value, "pwd ", 4)))
		return (g_exitvalue = ms_pwd(removequotes(value)));
	else if (!(ft_strncmp(value, "export", 6)))
		return (g_exitvalue = ms_export(removequotes(value), data));
	else if (!(ft_strncmp(value, "unset ", 6)))
		return (g_exitvalue = ms_unset(removequotes(value), data));
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
		g_exitvalue = ms_cd(removequotes(value), data);
	else if (!(ft_strncmp(value, "export", 6)))
		g_exitvalue = ms_export(removequotes(value), data);
	else if (!(ft_strncmp(value, "unset ", 6)))
		g_exitvalue = ms_unset(removequotes(value), data);
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
