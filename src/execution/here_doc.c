/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 10:32:59 by asauvage          #+#    #+#             */
/*   Updated: 2026/04/27 10:56:07 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	read_heredoc(char *limiter, int fd, t_env *env, int quote)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			write(2, "Minishell : warning :  ", 24);
			write(2, "here-document delimited by end-of-file ('", 42);
			write(2, limiter, ft_strlen(limiter));
			write(2, "')\n", 4);
			return (fd);
		}
		if (!ft_strcmp(line, limiter))
			return (free(line), fd);
		if (!quote && !expander_simple_array(&line, env))
			return (free(line), fd);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	return (fd);
}

void	child_heredoc(char **limiter, int open_fd, char *tmp, t_env *env)
{
	int	quote;

	init_signal_heredoc();
	quote = check_quote_limiter(limiter);
	if (quote != 2)
		read_heredoc(*limiter, open_fd, env, quote);
	close(open_fd);
	free(tmp);
	clear_ast(env->first_node_ast);
	clear_env(&env);
	rl_clear_history();
	if (g_signal_status == 130)
		exit(130);
	exit(0);
}

int	end_heredoc(int open_fd, char *tmp, int status)
{
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
	close(open_fd);
	open_fd = open(tmp, O_RDWR, 0777);
	unlink(tmp);
	free(tmp);
	return (open_fd);
}

int	here_doc(t_ast *ast, char **limiter, t_env *env)
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
		child_heredoc(limiter, open_fd, tmp, env);
	waitpid(pid, &status, 0);
	return (end_heredoc(open_fd, tmp, status));
}
