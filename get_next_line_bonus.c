/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:52:48 by dehamad           #+#    #+#             */
/*   Updated: 2024/01/09 11:24:47 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	handle_free(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

static char	*handle_appendline(char *arr_fd, char *buff)
{
	char	*join;

	if (!arr_fd && *buff)
	{
		arr_fd = ft_strdup(buff);
		if (!arr_fd)
			return (NULL);
		return (arr_fd);
	}
	if (arr_fd && *buff)
	{
		join = ft_strjoin(arr_fd, buff);
		if (!join)
			return (handle_free(&arr_fd), NULL);
		return (handle_free(&arr_fd), join);
	}
	return (NULL);
}

static char	*handle_ret(char **arr_fd)
{
	char	*ret;
	char	*temp;
	char	*newline_ptr;

	newline_ptr = ft_strchr(*arr_fd, '\n');
	if (newline_ptr)
	{
		*newline_ptr = '\0';
		ret = ft_strjoin(*arr_fd, "\n");
		if (*(newline_ptr + 1))
		{
			temp = ft_strdup(newline_ptr + 1);
			if (!temp)
				return (handle_free(&ret), NULL);
			handle_free(arr_fd);
			*arr_fd = ft_strdup(temp);
			return (handle_free(&temp), ret);
		}
		return (handle_free(arr_fd), ret);
	}
	ret = ft_strdup(*arr_fd);
	return (handle_free(arr_fd), ret);
}

static char	*handle_read(char **arr_fd, int fd, size_t size)
{
	char	*buff;
	ssize_t	counter;

	counter = 1;
	size = BUFFER_SIZE;
	buff = malloc(sizeof(char) * (size + 1));
	if (!buff)
		return (NULL);
	ft_bzero(buff, size + 1);
	while (counter > 0)
	{
		counter = read(fd, buff, size);
		if (counter > 0)
			*arr_fd = handle_appendline(*arr_fd, buff);
		else if (counter == -1)
			return (handle_free(arr_fd), free(buff), NULL);
		if (!counter || ft_strchr(buff, '\n'))
			break ;
		ft_bzero(buff, counter);
	}
	if (*arr_fd)
		return (free(buff), handle_ret(arr_fd));
	else
		return (free(buff), NULL);
}

char	*get_next_line(int fd)
{
	static char	*arr[OPEN_MAX];

	if (BUFFER_SIZE >= INT_MAX || BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	if (!arr[fd])
		arr[fd] = NULL;
	return (handle_read(&arr[fd], fd, BUFFER_SIZE));
}
