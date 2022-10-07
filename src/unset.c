#include "../incs/minishell.h"

int look_for_var_in_array(char *cmd, t_data *data)
{
	int i;
	size_t len;
	i = -1;
	len = ft_strlen(cmd);
	
	while (data->env[++i])
	{
		if (!ft_strncmp(cmd, data->env[i], len))
		{
			//fucntion to remove env var
			printf("found it\n");
			return(1);
		}	
	}
	return(-1);
}

int ms_unset(char *cmd, t_data *data)
{
	char **var;

	if(!ft_strncmp(cmd, "unset\0", 6))
		printf("unset: not enough arguments\n");
	else
	{
		var = ft_split(cmd, ' ');
		if (look_for_var_in_array(var[1], data) == -1)
			printf("\n");
	}
	return(1);
}