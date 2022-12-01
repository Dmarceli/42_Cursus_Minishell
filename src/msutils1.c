/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msutils1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarceli <dmarceli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:16:48 by dmarceli          #+#    #+#             */
/*   Updated: 2022/12/01 13:42:45 by dmarceli         ###   ########.fr       */
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
