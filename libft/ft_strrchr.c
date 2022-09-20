/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarceli <dmarceli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 12:29:47 by dmarceli          #+#    #+#             */
/*   Updated: 2021/10/29 12:33:00 by dmarceli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*y;
	char	x;

	y = 0;
	x = c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == x)
			y = (char *)&s[i];
		i++;
	}
	if (x == '\0')
		return ((char *)&s[i]);
	if (y != 0)
		return (y);
	return (0);
}
