/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:39:14 by mhummel           #+#    #+#             */
/*   Updated: 2024/10/21 12:05:51 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*ft_substr_g(char const *s, unsigned int start, size_t len);
size_t	ft_strlen_g(const char *s);
char	*ft_strchr_g(const char *s, int c);
char	*ft_strdup_g(const char *s1);
char	*read_txt(int fd, char **buffer);
void	*ft_memcpy_g(void *dst, const void *src, size_t n);
char	*read_next(char *buffer);
char	*extract_line(char **buffer);
char	*append_buffer(char *acc, const char *buff, ssize_t n);
char	*get_next_line(int fd);

#endif
