#include "../incs/minishell.h"

int	is_builtin(char *value, t_data *data)
{
	if (!value)
		return (0);
	else if (!(ft_strncmp(value, "echo", 4)))
		return (echo(value));
	else if (!(ft_strncmp(value, "cd", 2)))
		return (ms_cd(value, data));
	else if (!(ft_strncmp(value, "pwd", 3)))
		return(ms_pwd(value));
	else if (!(ft_strncmp(value, "export", 6)))
		return (ms_export(value, data));
	else if (!(ft_strncmp(value, "unset",5)))
		return (ms_unset(value, data));
	else if (!(ft_strncmp(value, "env", 3)))
		return (env(data));
	else if (!(ft_strncmp(value, "exit", 4)))
	{
		return(ft_exit(value, data));
		// int i = -1;
		// while(++i < data->envlen)
		// 	free (data->env[i]);
		// exit(1);
	}
	else if (!(ft_strncmp(value, "clear", 6)))
		return(clear_screen());
	else
		return(executecmd(value, data));
}

