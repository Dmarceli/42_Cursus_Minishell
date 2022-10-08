#include "../incs/minishell.h"

int add_new_var(char *cmd, t_data *data)
{
	char **var;
	char *tmp;
	int i;

	i = 0;
	var = (char**)malloc(sizeof(cmd));
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
	if (!ft_strncmp(cmd, "export\0" , 8) || !ft_strncmp(cmd, "export \0" , 9))
		env(data);
	else
		return (add_new_var(cmd, data));
	return (1);
}