/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarceli <dmarceli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 18:26:45 by dmarceli          #+#    #+#             */
/*   Updated: 2022/10/29 23:01:54 by dmarceli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*newstring;
	int		counter;
	int		size;
	char	*str_copy;

	size = ft_strlen(s1);
	newstring = (char *)malloc((size + 1) * sizeof(char));
	if (!(newstring))
		return (0);
	counter = 0;
	str_copy = newstring;
	while (counter < size)
	{
		str_copy[counter] = s1[counter];
		counter++;
	}
	str_copy[counter] = '\0';
	return (newstring);
}