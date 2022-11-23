#include "../incs/minishell.h"

int	is_builtin(char *value, t_data *data)
{
	if (ft_strchr(value, '\'') || ft_strchr(value, '\"'))
	 	value = removequotes(value);
	if (!check_emptyprompt(value))
		return(printf("%s: command not found\n", value));
	if (!value)
		return (0);
	else if (!(ft_strncmp(value, "echo", 4)))
		return (data->lastexec = echo(value));
	else if (!(ft_strncmp(value, "cd", 2)))
		return (data->lastexec = ms_cd(value, data));
	else if (!(ft_strncmp(value, "pwd", 3)))
		return(data->lastexec = ms_pwd(value));
	else if (!(ft_strncmp(value, "export", 6)))
		return (data->lastexec = ms_export(value, data));
	else if (!(ft_strncmp(value, "unset",5)))
		return (data->lastexec = ms_unset(value, data));
	else if (!(ft_strncmp(value, "env", 3)))
		return (env(data));
	else if (!(ft_strncmp(value, "exit", 4)))
		return(ft_exit(value, data));
	else
		return(executecmd(value, data));
}
