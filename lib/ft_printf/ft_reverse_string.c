/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 22:06:23 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/05/28 02:09:45 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_reverse_string(char *str, int len, int sig)
{
	int		i;
	char	temp;
	int		tam;

	tam = len - 1;
	i = sig;
	while (i <= len / 2 && i < tam)
	{
		temp = str[i];
		str[i] = str[tam];
		str[tam] = temp;
		i++;
		tam--;
	}
	return (str);
}
