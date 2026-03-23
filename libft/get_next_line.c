/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 15:10:58 by asauvage          #+#    #+#             */
/*   Updated: 2026/01/05 17:27:44 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*result_line(char *stash)
{
	int		i;
	char	*res;

	if (!stash || stash[0] == '\0')
		return (0);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	res = malloc(sizeof(char) * (i + (stash[i] == '\n') + 1));
	if (!res)
		return (0);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		res[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		res[i++] = '\n';
	res[i] = '\0';
	return (res);
}

static char	*ft_join(char *stash, char *buff)
{
	int		i;
	int		j;
	char	*res;

	res = malloc(sizeof(char) * (ft_strlen(stash) + ft_strlen(buff) + 1));
	if (!res)
	{
		if (stash)
			free(stash);
		return (0);
	}
	i = 0;
	j = 0;
	while (stash && stash[i])
		res[j++] = stash[i++];
	i = 0;
	while (buff && buff[i])
		res[j++] = buff[i++];
	res[j] = '\0';
	if (stash)
		free(stash);
	return (res);
}

static char	*clean_stash(char *stash)
{
	char	*new_stash;
	int		i;
	int		i_res;

	if (!stash)
		return (0);
	i = start_index(stash, 0);
	if (i == 0)
		return (0);
	new_stash = malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
	if (!new_stash)
	{
		free(stash);
		return (0);
	}
	i_res = 0;
	while (stash[i])
		new_stash[i_res++] = stash[i++];
	new_stash[i_res] = '\0';
	free(stash);
	return (new_stash);
}

static char	*search_line(int fd, char *buff, char *stash, ssize_t bytes)
{
	while (bytes > 0 && find_n(stash) == 1)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buff);
			if (stash)
				free(stash);
			return (0);
		}
		if (buff)
			buff[bytes] = '\0';
		stash = ft_join(stash, buff);
		if (!stash)
		{
			free(buff);
			return (0);
		}
	}
	free(buff);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buff;
	char		*res;
	ssize_t		bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(stash);
		return (0);
	}
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (0);
	bytes = 1;
	stash = search_line(fd, buff, stash, bytes);
	res = result_line(stash);
	stash = clean_stash(stash);
	return (res);
}
