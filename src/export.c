#include "../incs/minishell.h"

int add_new_var(char *cmd, t_data *data)
{
	char **var;
	char *tmp;
	int j;
	int in;
	char **in_out;

	j = 0;
	var = ft_split(cmd,' ');
	tmp	= ft_strdup(data->env[data->envlen - 1]);
	while(var[++j])
	{
		if(ft_strchr(var[j], '='))
		{
			in_out = ft_split(var[j], '=');
			in = look_for_var_in_array(in_out[0], data);
			free(in_out);
			if (in != -1)
			{
				free(data->env[in]);
				data->env[in] = ft_strdup(var[j]);
			}
			else
			{
				free(data->env[data->envlen - 1] );
				data->env[data->envlen - 1] = ft_strdup(var[j]);
				data->envlen++;
				data->env[data->envlen - 1] = ft_strdup(tmp);
			}
		}
		else 
			continue;
	}
	freearray(var);
	free(tmp);
	return (0);
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
	return (0);
}