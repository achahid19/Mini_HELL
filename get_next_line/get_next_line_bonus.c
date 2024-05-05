/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahid- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 15:36:00 by achahid-          #+#    #+#             */
/*   Updated: 2023/12/03 15:36:29 by achahid-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	new_line_finder(char *str);
static char		*substr(char *str);
static char		*get_line(char *str, char *tmp);
static void		free_buffers(char *s1, char *s2);

/**
 * get_next_line - function that reads a line by line from a fd
 * @fd: file descriptor
 * Return: the line readed from the fd
*/
char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*bytes_readed;
	ssize_t		bytes_count;

	bytes_count = 1;
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	bytes_readed = (char *)malloc(BUFFER_SIZE + 1);
	if (bytes_readed == NULL)
		return (NULL);
	while (bytes_count != 0 && !ft_strchr(buffer[fd], '\n'))
	{
		bytes_count = read(fd, bytes_readed, BUFFER_SIZE);
		if (bytes_count == -1)
		{
			free_buffers(bytes_readed, buffer[fd]);
			return (NULL);
		}
		bytes_readed[bytes_count] = '\0';
		buffer[fd] = ft_strjoin(buffer[fd], bytes_readed);
	}
	bytes_readed = get_line(buffer[fd], bytes_readed);
	buffer[fd] = substr(buffer[fd]);
	return (bytes_readed);
}

/**
 * new_line_finder - function that search for new line in str or eof
 * @str: the string
 * Return: index of the byte after '\n' or index of eof
*/
static size_t	new_line_finder(char *str)
{
	size_t	count;

	count = 0;
	while (str[count] && str[count] != '\n')
		count++;
	if (*(str + count) == '\n')
		count++;
	return (count);
}

/**
 * substr - function that allocates memory to create a substring
 * @str: the string from where the substr is created
 * Return: the substring, othewise NULL
*/
static char	*substr(char *str)
{
	char	*substr;
	size_t	count;
	size_t	count1;

	count = 0;
	count1 = 0;
	if (!*str)
		return (free(str), NULL);
	count = new_line_finder(str);
	substr = (char *)malloc((ft_strlen(str) - count) + 1);
	if (substr == NULL)
		return (NULL);
	while (str[count])
		substr[count1++] = str[count++];
	substr[count1] = '\0';
	if (*substr == '\0')
	{
		free(substr);
		free(str);
		return (NULL);
	}
	free(str);
	return (substr);
}

/**
 * get_line - function that allocate memory to retrieve a line from str
 * @str: the string form where the line is retrieved
 * Return: the line, otherwise NULL
*/
static char	*get_line(char *str, char *tmp)
{
	char	*new_line;
	size_t	count;

	free(tmp);
	count = 0;
	if (!str || *str == '\0')
		return (NULL);
	count = new_line_finder(str);
	new_line = (char *)malloc(count + 1);
	if (new_line == NULL)
		return (NULL);
	count = 0;
	while (str[count] && str[count] != '\n')
	{
		new_line[count] = str[count];
		count++;
	}
	if (str[count] == '\n')
	{
		new_line[count] = str[count];
		count++;
	}
	new_line[count] = '\0';
	return (new_line);
}

/**
 * free_buffers - function that frees buffers
 * @s1: pointer to the first buffer
 * @s2: pointer to the second buffer
 * Return: void.
*/
static void	free_buffers(char *s1, char *s2)
{
	free(s1);
	free(s2);
}
/*
#include <stdio.h>
#include <fcntl.h>
int main(void)
{
	int fd = open("test.txt", O_CREAT, "rw");
	int st = open("test1.txt", O_CREAT, "rw");
	char *str, *ptr;

	for (int count = 0; count < 2; count++)
	{
		str = get_next_line(fd);
		printf("str: %s\n", str);
		free(str);
		ptr = get_next_line(st);
		printf("ptr: %s\n", ptr);
		free(ptr);
	}
	return (0);
} */
