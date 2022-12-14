/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 17:45:42 by dmarceli          #+#    #+#             */
/*   Updated: 2022/12/14 16:19:12 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*test_path(char **possible_path, char *cmd)
{
	char	*tmp;
	char	*test_cmd;
	int		i;

	i = -1;
	while (possible_path[++i])
	{
		tmp = ft_strjoin(possible_path[i], "/");
		test_cmd = ft_strjoin(tmp, cmd);
		if (access(test_cmd, F_OK) < 0)
		{
			free(test_cmd);
			free(tmp);
		}
		else
		{
			freearray(possible_path);
			free(test_cmd);
			return (tmp);
		}
	}
	freearray(possible_path);
	return (0);
}

char	*handlepath(char *cmd, t_data *data)
{
	char	**possible_path;
	int		pos;

	pos = look_for_var_in_array("PATH", data);
	if (pos == -1)
		return (0);
	possible_path = ft_split(data->env[pos], ':');
	return (test_path(possible_path, cmd));
}

void	execprocess(char *cmd, t_data *data, char *path)
{
	char	cwd[1040];

	if (!ft_strncmp("./", data->exec[0], 2))
	{
		if (getcwd(cwd, sizeof(cwd)))
			path = ft_strdup(cwd);
		path = ft_strjoin(path, "/");
	}
	else if (cmd[0] != '/')
	{
		path = handlepath(data->exec[0], data);
		if (!path)
		{
			// if (ft_strchr(cmd, '\\'))
			// 	cmd = remove_escape(cmd);
			cmd = removequotes(cmd);
			printf("%s: command not found\n", cmd);
			exit (127);
		}
		data->exec[0] = ft_strjoin(path, data->exec[0]);
	}
	if (execve(data->exec[0], data->exec, data->env) == -1)
		printf("%s: command not found\n", cmd);
	freearray(data->exec);
	exit(126);
}

int	executecmd(char *cmd, t_data *data)
{
	int		a;
	char	*path;

	path = NULL;
	if (ft_strchr(cmd, ' '))
		data->exec = ft_split(cmd, ' ');
	else
	{
		data->exec = (char **)malloc(sizeof(char *) * 2);
		data->exec[0] = ft_strdup(cmd);
		data->exec[1] = NULL;
	}
	a = fork();
	if (!a)
		execprocess(cmd, data, path);
	freearray(data->exec);
	waitpid(a, &g_exitvalue, 0);
	g_exitvalue = exit_status(g_exitvalue);
	wait(0);
	return (0);
}
