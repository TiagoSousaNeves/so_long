/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:18:56 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/08/09 02:24:59 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

char		*ft_get_next_line(int fd);
char		*ft_strchr(const char *str, int c);
char		*ft_strdup(const char *str);
char		*ft_strjoin(const char *s1, const char *s2);
size_t		ft_strlen(const char *str);
#endif
