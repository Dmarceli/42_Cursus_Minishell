#include "../incs/minishell.h"

int add_new_var(char *cmd, t_data *data)
{
	char **var;
	char *tmp;
	int i;

	i = 0;
	var = ft_split(cmd,' ');
	if(ft_strchr(var[1], '='))
	{
		var[1] = ft_strtrim(var[1] ," ");
		while (data->env[i])
			i++;
		tmp = ft_strdup(data->env[--i]);
		data->env[i] = ft_strdup(var[1]);
		data->env[++i] = ft_strdup(tmp);
		free(tmp);
		free(var);
		data->envlen++;
		return (1);
	}
	else 
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
		return (add_new_var(cmd, data));
	return (1);
}