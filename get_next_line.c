/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haykharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:45:58 by haykharu          #+#    #+#             */
/*   Updated: 2025/02/22 15:03:47 by haykharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strjoin(char *s1, char c)
{
	size_t	len1;
	size_t	i;
	char	*str;

	len1 = 0;
	while (s1[len1] != '\0')
		++len1;
	str = (char *) malloc(len1 + 1 + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		++i;
	}
	str[i++] = c;
	str[i] = '\0';
	return (str);
}

static char	*ft_strdup(char *s1)
{
	size_t	len;
	size_t	i;
	char	*dest;

	if (!s1)
		return (NULL);
	len = 0;
	while (s1[len] != '\0')
		++len;
	dest = (char *)malloc(len + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		dest[i] = s1[i];
		++i;
	}
	dest[i] = '\0';
	return (dest);
}

static char	*ft_add_str(char add, int mode)
{
	static char	*str;
	char		*tmp;

	if (mode == 2)
	{
		str = ft_strdup("");
		return (str);
	}
	else if (mode == 3)
	{
		free(str);
		return (NULL);
	}
	else if (add)
	{
		tmp = ft_strjoin(str, add);
		if (!tmp)
			return (NULL);
		free(str);
		str = tmp;
		if (add != '\n')
			return (NULL);
		return (str);
	}
	return (str);
}

static char	*ft_clear(char **str, int only)
{
	if (str && *str)
		free(*str);
	if (only)
		return (ft_add_str('\0', 1));
	ft_add_str('\0', 3);
	return (NULL);
}

char	*get_next_line(int fd)
{
	int		bytes_read;
	char	*buff;

	if (fd < 0)
		return (NULL);
	buff = (char *) malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	bytes_read = read(fd, buff, BUFFER_SIZE);
	if (!ft_add_str('\0', 2) || bytes_read <= 0)
		return (ft_clear(&buff, 0));
	buff[bytes_read] = '\0';
	while (*buff != '\0' && bytes_read)
	{
		if (ft_add_str(*buff, 1))
			return (ft_clear(&buff, 1));
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
			return (ft_clear(&buff, 0));
		buff[bytes_read] = '\0';
	}
	if (bytes_read == 0)
		return (ft_clear(&buff, 1));
	return (NULL);
}
