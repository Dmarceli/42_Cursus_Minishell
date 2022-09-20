/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarceli <dmarceli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 11:06:12 by dmarceli          #+#    #+#             */
/*   Updated: 2021/10/26 12:21:18 by dmarceli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*c;

	c = (char *)s;
	i = -1;
	while (++i < n)
		c[i] = 0;
}

// #include <string.h>
// #include <stdio.h>
// int main (void)
// {
//     char s[100] = "vou de cana";
//     printf("--------Test de ft_bzero-------\n");
// 	bzero(s, 3);
// 	ft_bzero(s, 3);
// 	int		i;
// 	i = 0;
// 	while (i < 5 && s[i] == s[i])
// 		i++;
// 	if (i == 5)
// 		printf("OK\n");
// 	else
// 		printf("Failed");

// }
