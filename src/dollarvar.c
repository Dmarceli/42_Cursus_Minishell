#include "../incs/minishell.h"

char	*join_strs(char **strs)
{
	int i;
	int j;
	i = -1;
	j = -1;
	while (strs[++i])
		strs[i] = ft_strjoin(strs[i], " ");
	i = -1;
	while (strs[++i])
		strs[i + 1] = ft_strjoin(strs[i], strs[i + 1]);
	while (strs[++j] && j != (i - 1))
		free(strs[j]);
	return(strs[i - 1]);
}

int findvar(char *cmd, t_data *data)
{
	(void)data;
	int i;
	char *var;

	i = -1;
	var = ft_substr(cmd, 1, (ft_strlen(cmd)));
	while(data->env[++i])
	{
		if(!ft_strncmp(var, data->env[i], ft_strlen(var)))
		{
			free(var);
			return(i);
		}
	}
	free(var);
	return (0);
}

char *handle_dollar(char *cmd, t_data *data)
{
	char **j;
	char *value;
	int i;
	int k;

	i = 0;
	j = ft_split(cmd, ' ');
	while (ft_strchr(j[i], '$') == NULL)
		i++;
	k = findvar(j[i], data);
	if (k)
	{
		value = ft_substr(ft_strchr(data->env[k], '='), 1, ft_strlen(data->env[k]));
		j[i] = ft_strdup(value);
		free(value);
		value = join_strs(j);
		free(j);
		return (value);
	}
	else
		return(0);
}