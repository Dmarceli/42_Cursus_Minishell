#include "../incs/minishell.h"

int add_new_var(char *cmd, t_data *data)
{
	char **var;
	char *tmp;
	int j;

	j = 0;
	var = ft_split(cmd,' ');
	tmp	= ft_strdup(data->env[data->envlen - 1]);
	while(var[++j])
	{
		if(ft_strchr(var[j], '='))
		{
			data->env[data->envlen - 1] = ft_strdup(var[j]);
			data->envlen++;
		}
		else 
			continue;
	}
	data->env[data->envlen -1] = ft_strdup(tmp);
	freearray(var);
	free(tmp);
	return (1);
}	

int ms_export(char *cmd , t_data *data)
{
	int i;

	i = -1;
	if (!ft_strncmp(cmd, "export\0" , 8) || !ft_strncmp(cmd, "export \0" , 9))
	{
		while(++i < data->envlen)
			printf("declare -x %s\n", data->env[i]);
	}
	else
		add_new_var(cmd, data);
	free(cmd);
	return (1);
}