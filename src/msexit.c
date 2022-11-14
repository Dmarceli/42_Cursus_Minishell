#include "../incs/minishell.h"


int	ft_exit(char *cmd, t_data *data)
{
	char **value;
	if (ft_strchr(cmd, ' '))
	{
		value = ft_split(cmd, ' ');
		if (value[2])
			return(printf("exit: too many arguments"));
		else if(!is_numeric(value[1]))
			return(printf("exit: %s:numeric argument required", value[1]));
		else
		{
			int exit_status = ft_atoi(value[1]);
			freearray(value);
			freearray(data->env);
			exit(exit_status);
		}
	}
	else
	{
		freearray(data->env);
		exit(data->lastexec);
	}
}	