/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strerror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:32:26 by mhummel           #+#    #+#             */
/*   Updated: 2024/10/23 12:34:15 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strerror_part2(int errnum)
{
	if (errnum == EPIPE)
		return ("Broken pipe");
	else if (errnum == EMFILE)
		return ("Too many open files");
	else if (errnum == EFAULT)
		return ("Bad address");
	else if (errnum == EBUSY)
		return ("Device or resource busy");
	else if (errnum == ENFILE)
		return ("Too many open files in system");
	return ("Unknown error");
}

char	*ft_strerror(int errnum)
{
	if (errnum == EACCES)
		return ("Permission denied");
	else if (errnum == ENOENT)
		return ("No such file or directory");
	else if (errnum == EISDIR)
		return ("Is a directory");
	else if (errnum == ENOTDIR)
		return ("Not a directory");
	else if (errnum == ENOMEM)
		return ("Cannot allocate memory");
	else if (errnum == EAGAIN)
		return ("Resource temporarily unavailable");
	else if (errnum == EBADF)
		return ("Bad file descriptor");
	else if (errnum == EINVAL)
		return ("Invalid argument");
	else if (errnum == EEXIST)
		return ("File exists");
	return (ft_strerror_part2(errnum));
}
