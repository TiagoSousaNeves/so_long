/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 22:31:27 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/05/28 02:09:45 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strndup(const char *str, int n)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = malloc(n + 1);
	if (ptr == NULL)
		return (NULL);
	while (str[i] && n > 0)
	{
		ptr[i] = str[i];
		i++;
		n--;
	}
	ptr[i] = '\0';
	return (ptr);
}
