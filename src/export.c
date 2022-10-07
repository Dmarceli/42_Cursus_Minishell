#include "../incs/minishell.h"

int add_new_var(char *cmd, t_data *data)
{
	char **var;
	int i;
	char *tmp;


	i = 0;

	var = (char**)malloc(sizeof(cmd));
	var = ft_split(cmd,' ');
	var[1] = ft_strtrim(var[1] ," ");
	while (data->env[i])
		i++;
	tmp = ft_strdup(data->env[--i]);
	data->env[i] = ft_strdup(var[1]);
	data->env[++i] = ft_strdup(tmp);
	data->env[++i] = 0;
	free(tmp);
	free(var);
	return (1);
	data->envlen++;
}

int ms_export(char *cmd , t_data *data)
{
	if (!ft_strncmp(cmd, "export\0" , 8) || !ft_strncmp(cmd, "export \0" , 9))
		env(data);
	else
		return (add_new_var(cmd, data));
	return (1);
}