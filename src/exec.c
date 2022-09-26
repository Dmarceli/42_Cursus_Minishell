#include "../incs/minishell.h"

char *getpath(t_data *data)
{
	int i;
	char **path;

	i = -1;
	while (data->env[++i])
	{
		if (ft_strncmp("PATH=", data->env[i], 5) == 0)
		{
			path = ft_split(data->env[i], '=');
			return(path[1]);
		}
	}
	return(0);
}

void exec_cmd(t_data *data, char **cmd)
{
	char *path;
	int pid;
	int z;
	(void)cmd;
	char* const args[] = { "/bin/", NULL};

	path = "bin/ls";//getenv("PATH");
	pid = fork();
	if (pid == 0)
	{
		z = execve(path, args, data->env);
		printf("%d\n", z);
	}
}