/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:40:54 by mhummel           #+#    #+#             */
/*   Updated: 2024/04/09 13:22:41 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	clear_buffer(char **buffer)
{
	if (*buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
}

char	*append_buffer(char *acc, const char *buff, ssize_t n)
{
	char	*new_str;
	size_t	acc_len;
	size_t	new_len;

	acc_len = 0;
	if (acc != NULL)
		acc_len = ft_strlen(acc);
	new_len = acc_len + n;
	new_str = malloc(new_len + 1);
	if (new_str == NULL)
	{
		free(acc);
		return (NULL);
	}
	if (acc != NULL)
	{
		ft_memcpy(new_str, acc, acc_len);
		free(acc);
	}
	ft_memcpy(new_str + acc_len, buff, n);
	new_str[new_len] = '\0';
	return (new_str);
}

char	*extract_line(char **buffer)
{
	char	*line;
	char	*new_buffer;
	char	*n_ptr;
	size_t	line_len;

	n_ptr = ft_strchr(*buffer, '\n');
	if (!n_ptr)
		line_len = ft_strlen(*buffer);
	else
		line_len = n_ptr - *buffer + 1;
	line = ft_substr(*buffer, 0, line_len);
	if (!line)
		return (clear_buffer(buffer), NULL);
	if (n_ptr)
	{
		new_buffer = ft_strdup(n_ptr + 1);
		clear_buffer(buffer);
		*buffer = new_buffer;
	}
	else
		clear_buffer(buffer);
	if (*buffer && **buffer == '\0')
		clear_buffer(buffer);
	return (line);
}

char	*read_txt(int fd, char **buffer)
{
	char	temp[BUFFER_SIZE + 1];
	ssize_t	bytes_read;

	bytes_read = read(fd, temp, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		temp[bytes_read] = '\0';
		*buffer = append_buffer(*buffer, temp, bytes_read);
		if (!*buffer)
			return (NULL);
		if (ft_strchr(temp, '\n'))
			break ;
		bytes_read = read(fd, temp, BUFFER_SIZE);
	}
	if (bytes_read < 0)
		return (clear_buffer(buffer), NULL);
	return (*buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!read_txt(fd, &buffer) && !buffer)
		return (NULL);
	line = extract_line(&buffer);
	return (line);
}
