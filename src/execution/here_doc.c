/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 10:32:59 by asauvage          #+#    #+#             */
/*   Updated: 2026/05/02 17:54:13 by asauvage         ###   ########.fr       */
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
			if (g_signal_status != 130)
			{
				write(2, "Minishell : warning :  ", 24);
				write(2, "here-document delimited by end-of-file ('", 42);
				write(2, limiter, ft_strlen(limiter));
				write(2, "')\n", 4);
			}
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
	{
		close(STDOUT_FILENO);
		exit(130);
	}
	close_std_fd();
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
		return (-3);
	}
	close(open_fd);
	open_fd = open(tmp, O_RDWR, 0777);
	unlink(tmp);
	free(tmp);
	return (open_fd);
}

int	here_doc(char **limiter, t_env *env)
{
	int		open_fd;
	char	*tmp;
	pid_t	pid;
	int		status;

	tmp = NULL;
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

int	fill_here_doc(t_ast *ast, t_env *env)
{
	int	i;

	if (ast->type == PIPE)
	{
		i = fill_here_doc(ast->l_child, env);
		if (i == -1 || i == -3)
			return (i);
		i = fill_here_doc(ast->r_child, env);
		if (i == -1 || i == -3)
			return (i);
		return (1);
	}
	i = -1;
	while (ast->limiter && ast->limiter[++i])
	{
		if (ast->fd[0] > -1)
		{
			close(ast->fd[0]);
			ast->fd[0] = -2;
		}
		ast->fd[0] = here_doc(&ast->limiter[i], env);
		if (ast->fd[0] == -1 || ast->fd[0] == -3)
			return (ast->fd[0]);
	}
	return (1);
}
