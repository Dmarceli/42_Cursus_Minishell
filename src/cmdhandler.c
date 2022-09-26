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
		return(0);
}