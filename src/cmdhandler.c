/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdhandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielsequeira <danielsequeira@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:35:28 by dmarceli          #+#    #+#             */
/*   Updated: 2022/12/10 17:55:02 by danielseque      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	is_builtin(char *value, t_data *data)
{

	if ((value[0] == '\'' || value[0] == '\"') && 
		(value[ft_strlen(value) - 1] == '\'' || value[ft_strlen(value) - 1] == '\"') && ft_strchr(value, ' '))
		return (executecmd(value, data));
	if (!check_emptyprompt(value))
		return (printf("%s: command not found\n", value));
	if (!value)
		return (0);
	else if (!(ft_strncmp(value, "echo ", 5)))
		return (exitvalue = echo(removequotes(value)));
	else if (!(ft_strncmp(value, "cd ", 3)))
		return (exitvalue = ms_cd(removequotes(value), data));
	else if (!(ft_strncmp(value, "pwd ", 4)))
		return (exitvalue = ms_pwd(removequotes(value)));
	else if (!(ft_strncmp(value, "export", 6)))
		return (exitvalue = ms_export(removequotes(value), data));
	else if (!(ft_strncmp(value, "unset ", 6)))
		return (exitvalue = ms_unset(removequotes(value), data));
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
		exitvalue = ms_cd(removequotes(value), data);
	else if (!(ft_strncmp(value, "export", 6)))
		exitvalue = ms_export(removequotes(value), data);
	else if (!(ft_strncmp(value, "unset ", 6)))
		exitvalue = ms_unset(removequotes(value), data);
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
