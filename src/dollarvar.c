#include "../incs/minishell.h"

char	*join_strs(char **strs)
{
	int		i;
	char	**tmp;
	char	*ret;
	char	*tj;
	
	tmp = malloc(sizeof(char *) * big_len(strs));
	i = -1;
	while (strs[++i])
	{
		tj = ft_strjoin(" ", strs[i + 1]);
		tmp[i] = ft_strjoin(strs[i], tj);
		free(tj);
	}
	ret = strdup(tmp[i - 2]);
	free_split(tmp);
	return(ret);
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
		free(j[i]);
		j[i] = ft_strdup(value);
		free(value);
		value = join_strs(j);
		free_split(j);
		return (value);
	}
	else
	{
		free_split(j);
		return(0);
	}
}

void	free_split(char **sp)
{
	int	fr;

	fr = -1;
	while(sp[++fr] != NULL)
		free(sp[fr]);
	free(sp);
}
