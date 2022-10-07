#include "../incs/minishell.h"

void	initenv(char **envs, t_data *data)
{
	size_t i;
	i = 0;

	while (envs[i])
		i++;
	data->env = (char **)malloc(sizeof(char *) * (i + 10));
	i = -1;
	while (envs[++i])
		data->env[i] = ft_strdup(envs[i]);
	data->env[i] = 0;
	data->envlen = i;
}


int env(t_data *data)
{
	int i ;
	i = -1;
	while(data->env[++i])
		printf("%s\n", data->env[i]);
	return(1);
}