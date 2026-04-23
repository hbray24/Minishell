/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 10:32:59 by asauvage          #+#    #+#             */
/*   Updated: 2026/04/23 16:43:21 by hbray            ###   ########.fr       */
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
		perror("Minishell :open_file");
		return (fd);
	}
	return (fd);
}

int	read_heredoc(char *limiter, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			write (1, "\n", 1);
			return (fd);
		}
		if (!ft_strcmp(line, limiter))
		{
			free(line);
			return (fd);
		}
		write(fd, line, ft_strlen(line));
		write (fd, "\n", 1);
		free(line);
	}
	return (fd);
}

int	here_doc(t_ast *ast, char *limiter)
{
	int		open_fd;
	char	*tmp;
	pid_t	pid;
	int		status;

	tmp = NULL;
	if (ast->fd[0] > -1)
		close(ast->fd[0]);
	open_fd = open_file(&tmp);
	if (open_fd == -1)
		return (open_fd);
	g_signal_status = 0;
	gestion_term(0);
	ignore_signal();
	pid = fork();
	if (pid == -1)
	{
		perror("Minishell :here_doc");
		return (-1);
	}
	if (pid == 0)
	{
		init_signal_heredoc();
		read_heredoc(limiter, open_fd);
		close(open_fd);
		free(tmp);
		exit(0);
	}
	waitpid(pid, &status, 0);
	gestion_term(1);
	restore_signal();
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		g_signal_status = 130;
		close(open_fd);
		unlink(tmp);
		free(tmp);
		return (-1);
	}
	close (open_fd);
	open_fd = open(tmp, O_RDWR, 0777);
	unlink(tmp);
	free(tmp);
	return (open_fd);
}
