#include "../incs/minishell.h"

int env(t_data *data)
{
	int i = -1;
	while(data->env[++i])
		printf("%s\n", data->env[i]);
	return(1);
}