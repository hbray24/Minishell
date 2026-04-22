/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 10:32:59 by asauvage          #+#    #+#             */
/*   Updated: 2026/04/22 16:20:15 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	read_heredoc(char *limiter, int fd)
{
	char	*line;
	int		len;

	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
		{
			write (1, "\n", 1);
			return (fd);
		}
		len = ft_strlen(line) - 1;
		if (len > -1)
			line[len] = '\0';
		if (!ft_strcmp(line, limiter))
		{
			free(line);
			return (fd);
		}
		line[len] = '\n';
		write(fd, line, len + 1);
		free(line);
	}
	return (fd);
}

int	here_doc(t_ast *ast, char *limiter)
{
	int		open_fd;
	char	*tmp;

	tmp = NULL;
	if (ast->fd[0] > -1)
		close(ast->fd[0]);
	open_fd = open_file(&tmp);
	if (open_fd == -1)
		return (open_fd);
	if (read_heredoc(limiter, open_fd) == -2)
	{
		perror("Minishell");
		return (open_fd);
	}
	close (open_fd);
	open_fd = open(tmp, O_RDWR, 0777);
	unlink(tmp);
	free(tmp);
	return (open_fd);
}
