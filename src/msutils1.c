/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msutils1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:16:48 by dmarceli          #+#    #+#             */
/*   Updated: 2022/12/05 17:57:52 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*justthevar(char *str)
{
	int		len;
	char	*ret;
	int		i;

	len = 0;
	i = 0;
	while (str[len] != '=')
		len++;
	ret = malloc(sizeof(char) * len + 1);
	ret[len] = '\0';
	while (i < len)
	{
		ret[i] = str[i];
		i++;
	}
	return (ret);
}

int	big_len(char **str)
{
	int	counter;

	counter = 0;
	while (str[counter] != NULL)
		counter++;
	return (counter);
}

char	*no_var_to_expand(char **j, int i, char *value)
{
	free(j[i]);
	j[i] = ft_strdup("");
	value = join_strs(j, " ", -1);
	freearray(j);
	return (value);
}
