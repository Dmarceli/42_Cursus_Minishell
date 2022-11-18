#include "../incs/minishell.h"

char *handlepath(char *cmd, t_data *data)
{
	char 	**possible_path;
	char	*test_cmd;
	int 	pos;
	char 	*tmp;
	int		i;

	i  = -1;
	pos = look_for_var_in_array("PATH", data);
	if (pos == -1)
		return(0);
	possible_path = ft_split(data->env[pos], ':');
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
	int 	exitvalue;
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
				exit (127);
			}
			data->exec[0] = ft_strjoin(path, data->exec[0]);
		}
		if (execve(data->exec[0], data->exec, data->env) == -1)
			printf("Error: %s not found\n", cmd);
		freearray(data->exec);
		exit(126);
	}
	freearray(data->exec);
	waitpid(a, &exitvalue, 0);
	data->lastexec= WEXITSTATUS(exitvalue);
	wait(0);
	return(0);
}