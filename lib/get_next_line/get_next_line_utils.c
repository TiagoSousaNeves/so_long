/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:49:36 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/08/05 14:01:05 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *str);
char	*ft_strjoin(const char *s1, const char *s2);
size_t	ft_strlen(const char *str);

char	*ft_strchr(const char *str, int c)
{
	int				i;
	char			*ptr;
	unsigned char	equal_c;

	i = 0;
	ptr = NULL;
	equal_c = (unsigned char)c;
	while (str[i])
	{
		if (str[i] == equal_c)
		{
			ptr = (char *)&str[i];
			return (ptr);
		}
		i++;
	}
	if (equal_c == '\0')
		return (ptr = (char *)&str[i]);
	return (ptr);
}

char	*ft_strdup(const char *str)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = malloc(ft_strlen(str) + 1);
	if (ptr == NULL)
		return (NULL);
	while (str[i])
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (res == NULL)
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}
