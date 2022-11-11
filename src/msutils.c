#include "../incs/minishell.h"

void freearray(char **arr)
{
	int i;
	i = -1;
	while(arr[++i])
	{
		if(arr[i])
			free(arr[i]);
	}
	free(arr);
	arr = NULL;
}

int look_for_var_in_array(char *cmd, t_data *data)
{
	int i;
	size_t len;

	i = -1;
	len = ft_strlen(cmd);	
	while (data->env[++i])
	{
		if (!ft_strncmp(cmd, data->env[i], len))
			return(i);
	}
	return(-1);
}

int is_numeric(char *value)
{
    int j;
    j = ft_strlen(value);
    while(j--)
    {
        if(value[j] >= '0' && value[j] <= '9')
            continue;
		else
        	return (0);
    }
    return (1);
}

