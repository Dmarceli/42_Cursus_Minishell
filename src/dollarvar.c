/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollarvar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarceli <dmarceli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:44:01 by dmarceli          #+#    #+#             */
/*   Updated: 2022/12/01 15:23:27 by dmarceli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*new_var(char **j, int i, int k, t_data *data)
{
	char	*value;

	value = NULL;
	if (k != -1)
	{	
		value = ft_substr(ft_strchr(data->env[k], '='), 1,
				ft_strlen(data->env[k]));
		free(j[i]);
		j[i] = ft_strdup(value);
		free(value);
		value = join_strs(j, " ", -1);
		freearray(j);
		if (!ft_strchr(value, '$'))
			return (value);
		else
		{
			free(value);
			value = handle_dollar(value, data);
			return (value);
		}
	}
	else
		return (no_var_to_expand(j, i, value));
}

char	*handle_dollar_in(char **j, int i, t_data *data)
{
	char	*value;

	value = ft_itoa(data->lastexec);
	free(j[i]);
	j[i] = ft_strdup(value);
	free(value);
	value = join_strs(j, " ", -1);
	freearray(j);
	if (!ft_strchr(value, '$'))
		return (value);
	else
	{
		value = handle_dollar(value, data);
		return (value);
	}
}

char	*handle_singlequotes(char **j, int i)
{
	char	*tmp;
	char	*value;

	tmp = ft_strtrim(j[i], "\'" );
	free(j[i]);
	j[i] = ft_strtrim(tmp, "\'" );
	free(tmp);
	if (big_len(j) != 1)
		value = join_strs(j, " ", -1);
	else
		value = ft_strdup(j[i]);
	freearray(j);
	return (value);
}

int	findvar(char *cmd, t_data *data)
{
	int		i;
	char	*var;
	char	*tmp;
	char 	*tmp2 = NULL;

	i = -1;
	if (ft_strchr(cmd, '\"'))
		var = ft_strtrim(cmd, "\"");
	else
		var = ft_substr(cmd, 1, (ft_strlen(cmd)));
	tmp = ft_strtrim(var, " $");
	while (data->env[++i])
	{
		tmp2 = justthevar(data->env[i]);
		if (!ft_strncmp(tmp, tmp2, ft_strlen(tmp2)))
		{
			free(var);
			free(tmp);
			free (tmp2);
			return (i);
		}
		free (tmp2);
	}
	free(tmp);
	free(var);
	return (-1);
}

char	*handle_dollar(char *cmd, t_data *data)
{
	char	**j;
	int		i;
	int		k;

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
	if (ft_strchr(j[i], '\''))
		return (handle_singlequotes(j, i));
	if (ft_strchr(j[i], '?'))
		return (handle_dollar_in(j, i, data));
	k = findvar(j[i], data);
	return (new_var(j, i, k, data));
}
