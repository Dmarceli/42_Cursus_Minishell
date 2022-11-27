#include "../incs/minishell.h"

char	*join_strs(char **str_chunks, char *sep, int limiter)
{
	int		k;
	char	*complete_str;
	k = -1;
	complete_str = 0;
	while (str_chunks[++k] && (k < limiter || limiter < 0))
	{
		if (!complete_str)
			complete_str = ft_strjoin(sep, str_chunks[k]);
		else
		{
			complete_str = ft_strjoin(complete_str, sep);
			complete_str = ft_strjoin(complete_str, str_chunks[k]);
		}
	}
	if (complete_str)
		return (ft_strjoin(complete_str, sep));
	return (complete_str);
}

int findvar(char *cmd, t_data *data)
{
	(void)data;
	int i;
	char *var;
	char *tmp;

	i = -1;
	if(ft_strchr(cmd, '\"'))
		var = ft_strtrim(cmd, "\"");
	else
		var = ft_substr(cmd, 1, (ft_strlen(cmd)));
	tmp = ft_strtrim(var, " $");
	while(data->env[++i])
	{
		if(!ft_strncmp(tmp, data->env[i], ft_strlen(tmp)))
		{
			free(var);
			free(tmp);
			return(i);
		}
	}
	free(tmp);
	free(var);
	return (-1);
}

char *handle_dollar(char *cmd, t_data *data)
{
	char **j;
	char *value;
	char *tmp;
	int i;
	int k;

	i = 0;
	if (ft_strchr(cmd, ' '))
	{
		j = ft_split(cmd, ' ');
		while (ft_strchr(j[i], '$') == NULL)
			i++;
	}
	else
	{
		j = ft_split(cmd, '$');
		i = 1;
	}
	if(ft_strchr(j[i], '\''))
	{
		tmp = ft_strtrim(j[i], "\'" );
		free(j[i]);
		j[i] = ft_strtrim(tmp, "\'" );
		free(tmp);
		if (big_len(j) != 1)
			value = join_strs(j," ",-1);
		else
			value = ft_strdup(j[i]);
		free_split(j);
		return (value);
	}
	if(ft_strchr(j[i], '?'))
	{
		value = ft_itoa(data->lastexec);
		free(j[i]);
		j[i] = ft_strdup(value);
		free(value);
		value = join_strs(j, " ",-1);
		free_split(j);
		if (!ft_strchr(value, '$'))
			return (value);
		else
		{
			value = handle_dollar(value, data);
			return(value);
		}
	}
	k = findvar(j[i], data);
	if (k != -1)
	{
		value = ft_substr(ft_strchr(data->env[k], '='), 1, ft_strlen(data->env[k]));
		free(j[i]);
		j[i] = ft_strdup(value);
		free(value);
		value = join_strs(j, " ",-1);
		free_split(j);
		if (!ft_strchr(value, '$'))
			return (value);
		else
		{
			value = handle_dollar(value, data);
			return(value);
		}
	}
	else
	{
		free(j[i]);
		j[i] = ft_strdup("");
		value = join_strs(j," ",-1);
		free_split(j);
		return(value);
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
