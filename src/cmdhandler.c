#include "../incs/minishell.h"



int	is_builtin(char *value, t_data *data)
{
	if (!value)
		return (0);
	else if (!(ft_strncmp(value, "echo", 4)))
		return (echo(value));
	else if (!(ft_strncmp(value, "cd", 2)))
		return (ms_cd(value));
	else if (!(ft_strncmp(value, "pwd", 3)))
		return(ms_pwd());
	else if (!(ft_strncmp(value, "export", 6)))
		return (1);
	else if (!(ft_strncmp(value, "unset",5)))
		return (1);
	else if (!(ft_strncmp(value, "env", 3)))
		return (env(data));
	else if (!(ft_strncmp(value, "exit", 4)))
		exit(1);
	else
		return(executecmd(value, data));
}

int	executecmd(char *cmd, t_data *data)
{
	int		a;
	char	*args[2];
	(void)cmd;
	a = fork();
	if (!a)
	{
		args[0] = ft_strdup("/bin/ls");
		args[1] = NULL;
		//args[2] = ft_strdup(cmd);
		if (execve("/bin/ls", args, data->env) == -1)
			printf("error\n");
		exit(0);
	}
	wait(0);
	return(0);
}