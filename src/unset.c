#include "../incs/minishell.h"

void	remove_var(t_data *data, int pos)
{
	int i;

	i = pos - 1;
	while (i++ < data->envlen - 1)
    	data->env[i] = data->env[i + 1];
	data->env[i] = 0;
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

int ms_unset(char *cmd, t_data *data)
{
	char **var;
	int pos;

	if(!ft_strncmp(cmd, "unset\0", 6))
		printf("unset: not enough arguments\n");
	else
	{
		var = ft_split(cmd, ' ');
		pos = look_for_var_in_array(var[1], data);
		if (pos == -1)
			printf("\n");
		else 
			remove_var(data, pos);
	}
	data->envlen--;
	return(1);
}