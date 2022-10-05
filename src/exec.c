#include "../incs/minishell.h"

int	executecmd(char *cmd, t_data *data)
{
	int		a;
	int 	i;
	char	**args;	

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
		args[0] = ft_strjoin("/bin/", data->exec[0]);
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