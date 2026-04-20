/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 10:32:59 by asauvage          #+#    #+#             */
/*   Updated: 2026/04/17 14:26:43 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file(char **tmp)
{
	int		nb;
	int		fd;
	char	*tmp_itoa;

	fd = -1;
	nb = 0;
	while (fd == -1 && nb < INT_MAX)
	{
		free(*tmp);
		tmp_itoa = ft_itoa(nb);
		*tmp = ft_strjoin("/tmp/tmp_file_here_doc", tmp_itoa);
		free(tmp_itoa);
		fd = open(*tmp, O_CREAT | O_EXCL | O_RDWR, 0777);
		nb++;
	}
	if (fd == -1)
	{
		perror("Minishell");
		return (fd);
	}
	return (fd);
}

int	here_doc(char **limiter)
{
	int		i;
	int		open_fd;
	char	*line;
	char	*tmp;

	tmp = NULL;
	i = 0;
	open_fd = open_file(&tmp);
	if (open_fd == -1)
		return (open_fd);
	while (limiter && limiter[i])
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
		{
			perror("Minishell");
			return (open_fd);
		}
		line[ft_strlen(line) - 1] = '\0';
		if (!ft_strcmp(line, limiter[i]))
		{
			free(line);
			if (!limiter[++i])
			{
				close (open_fd);
				open_fd = open(tmp, O_RDWR, 0777);
				break ;
			}
			else
				continue;
		}
		line[ft_strlen(line) - 1] = '\n';
		write(open_fd, line, ft_strlen(line));
		free(line);
	}
	unlink(tmp);
	free(tmp);
	return (open_fd);
}
