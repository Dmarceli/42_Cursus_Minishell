/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:27:16 by dmarceli          #+#    #+#             */
/*   Updated: 2022/12/16 01:44:03 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	export_new_var(t_data *data, char *var, char *tmp)
{
	free(data->env[data->envlen - 1]);
	data->env[data->envlen - 1] = ft_strdup(var);
	data->envlen++;
	data->env[data->envlen - 1] = ft_strdup(tmp);
	data->env[data->envlen] = NULL;
}

void	process_array(char **var, char *tmp, t_data *data)
{
	int		in;
	char	**in_out;
	int		j;

	j = 0;
	while (var[++j])
	{
		if (ft_strchr(var[j], '='))
		{
			in_out = ft_split(var[j], '=');
			in = look_for_var_in_array(in_out[0], data);
			freearray(in_out);
			if (in != -1)
			{
				free(data->env[in]);
				data->env[in] = ft_strdup(var[j]);
			}
			else
				export_new_var(data, var[j], tmp);
		}
		else
			continue ;
	}
	return ;
}

int	add_new_var(char *cmd, t_data *data)
{
	char	**var;
	char	*tmp;

	var = ft_split(cmd, ' ');
	tmp = ft_strdup(data->env[data->envlen - 1]);
	process_array(var, tmp, data);
	freearray(var);
	free(tmp);
	return (0);
}

int	ms_export(char *cmd, t_data *data)
{
	int	i;

	i = -1;
	if (!ft_strncmp(cmd, "export\0", 8) || !ft_strncmp(cmd, "export \0", 9))
	{
		while (++i < data->envlen)
			printf("declare -x %s\n", data->env[i]);
	}
	else
		add_new_var(cmd, data);
	return (0);
}
