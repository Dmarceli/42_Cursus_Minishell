#include "../incs/minishell.h"

char *handlepath(char *cmd, t_data *data)
{
	char **possible_path;
	char *test_cmd;
	char *tmp;
	(void)data;
	int i;

	i  = -1;
	possible_path = ft_split(getenv("PATH"), ':');
	while (possible_path[++i])
	{
		tmp = ft_strjoin(possible_path[i] , "/");
		test_cmd = ft_strjoin(tmp, cmd);
		if(access(test_cmd, F_OK) < 0)
		{
			free(test_cmd);
			free(tmp);
		}
		else
		{
			free(test_cmd);
			return(tmp);
		}
	}
	freearray(possible_path);
	return(0);
}

int	executecmd(char *cmd, t_data *data)
{
	int		a;
	char 	*path = NULL;
	char	cwd[1040];

	if (ft_strchr(cmd, ' '))
	 	data->exec = ft_split(cmd,' ');
	else
	{
		data->exec = (char**)malloc(sizeof(char *) * 2);
		data->exec[0] = ft_strdup(cmd);
		data->exec[1] = NULL;
	}
	a = fork();
	if (!a)
	{
		if (!ft_strncmp("./" , data->exec[0], 2))
		{
			if (getcwd(cwd, sizeof(cwd)))
				path = ft_strdup(cwd);
			path = ft_strjoin(path , "/");
		}
		else if (cmd[0] != '/')
		{
			path = handlepath(data->exec[0], data);
			if (!path)
			{
				printf("Error: %s not found\n", cmd);
				exit (0);
			}
			data->exec[0] = ft_strjoin(path, data->exec[0]);
		}
		if (execve(data->exec[0], data->exec, data->env) == -1)
			printf("Error: %s not found\n", cmd);
		freearray(data->exec);
		exit(0);
	}
	freearray(data->exec);
	wait(0);
	return(0);
}