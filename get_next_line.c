/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:52:48 by dehamad           #+#    #+#             */
/*   Updated: 2024/01/09 11:24:25 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	handle_free(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

static char	*handle_appendline(char *arr, char *buff)
{
	char	*join;

	if (!arr && *buff)
	{
		arr = ft_strdup(buff);
		if (!arr)
			return (NULL);
		return (arr);
	}
	if (arr && *buff)
	{
		join = ft_strjoin(arr, buff);
		if (!join)
			return (handle_free(&arr), NULL);
		return (handle_free(&arr), join);
	}
	return (NULL);
}

static char	*handle_ret(char **arr)
{
	char	*ret;
	char	*temp;
	char	*newline_ptr;

	newline_ptr = ft_strchr(*arr, '\n');
	if (newline_ptr)
	{
		*newline_ptr = '\0';
		ret = ft_strjoin(*arr, "\n");
		if (*(newline_ptr + 1))
		{
			temp = ft_strdup(newline_ptr + 1);
			if (!temp)
				return (handle_free(&ret), NULL);
			handle_free(arr);
			*arr = ft_strdup(temp);
			return (handle_free(&temp), ret);
		}
		return (handle_free(arr), ret);
	}
	ret = ft_strdup(*arr);
	return (handle_free(arr), ret);
}

static char	*handle_read(char **arr, int fd, size_t size)
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
			*arr = handle_appendline(*arr, buff);
		else if (counter == -1)
			return (handle_free(arr), free(buff), NULL);
		if (!counter || ft_strchr(buff, '\n'))
			break ;
		ft_bzero(buff, counter);
	}
	if (*arr)
		return (free(buff), handle_ret(arr));
	else
		return (free(buff), NULL);
}

char	*get_next_line(int fd)
{
	static char	*arr;

	if (BUFFER_SIZE >= INT_MAX || BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	if (!arr)
		arr = NULL;
	return (handle_read(&arr, fd, BUFFER_SIZE));
}
