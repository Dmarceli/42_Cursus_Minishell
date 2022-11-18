#include "../incs/minishell.h"


int	ft_exit(char *cmd, t_data *data)
{
	char **value;
	if (ft_strchr(cmd, ' '))
	{
		value = ft_split(cmd, ' ');
		int exit_status = ft_atoi(value[1]);
		if (value[2])
			return(printf("exit: too many arguments"));
		else if(!is_numeric(value[1]))
		{
			printf("exit: %s:numeric argument required\n", value[1]);
			freearray(value);
			freearray(data->env);
			exit(255);
		}
		else
		{
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