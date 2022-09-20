/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarceli <dmarceli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 11:06:44 by dmarceli          #+#    #+#             */
/*   Updated: 2021/10/27 12:44:28 by dmarceli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

// int	main(void)
// {
// 	char s[] = "	1234567890";
// 	printf("%d\n", ft _strlen(s));
// 	return ();
// }
// %

// 	int main(void)
// {
// 	char s[] = "1234567890";
// 	printf("%d\n", ft_ strlen(s));
// 	return (0);
// }%