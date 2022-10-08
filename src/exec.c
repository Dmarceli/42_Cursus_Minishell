#include "../incs/minishell.h"

char *handlepath(char *cmd, t_data *data)
{
	char **possible_path;
	char *test_cmd;
	(void)data;

	possible_path = ft_split(getenv("PATH"), ':');
	int i  = -1;
	while (possible_path[++i])
	{
		possible_path[i] = ft_strjoin(possible_path[i] , "/");
		test_cmd = ft_strjoin(possible_path[i], cmd);
		if(access(test_cmd, F_OK) < 0)
			free(test_cmd);
		else
		{
			free(possible_path);
			return(possible_path[i]);
		}
	}
	return("ERROR");
}


int	executecmd(char *cmd, t_data *data)
{
	int		a;
	int 	i;
	char	**args;
	char 	*path;

	i = 0;
	data->exec = (char**)malloc(sizeof(cmd));
	args = (char**)malloc(sizeof(cmd));
	if (ft_strchr(cmd, ' '))
	 	data->exec = ft_split(cmd,' ');
	else 
		data->exec[0] = ft_strdup(cmd);
	a = fork();
	if (!a)
	{
		path = handlepath(data->exec[0], data);
		args[0] = ft_strjoin(path, data->exec[0]);
		while (data->exec[++i])
			args[i] = ft_strdup(data->exec[i]);
		args[i] = NULL;
		if (execve(args[0], args, data->env) == -1)
			printf("Error: %s not found\n", cmd);
		exit(0);
	}
	wait(0);
	free(data->exec);
	free(args);
	return(0);
}