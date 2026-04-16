/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 10:32:59 by asauvage          #+#    #+#             */
/*   Updated: 2026/04/16 15:53:07 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file()
{
	int		nb;
	int		fd;
	char	*tmp;
	char	*tmp_itoa;

	fd = -1;
	nb = 0;
	while (fd == -1 && nb < INT_MAX)
	{
		tmp_itoa = ft_itoa(nb);
		tmp = ft_strjoin("/tmp/tmp_file_here_doc", tmp_itoa);
		free(tmp_itoa);
		fd = open(tmp, O_CREAT | O_EXCL | O_WRONLY, 0222);
		free(tmp);
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
	int		open;
	char	*line;

	i = 0;
	open = open_file();
	if (open == -1)
		return (open);
	while (limiter && limiter[i])
	{
		line = readline(">");
		if (!line)
		{
			perror("Minishell");
			return (open);
		}
		if (!ft_strcmp(line, limiter[i]))
		{
			free(line);
			if (!limiter[++i])
				return (open);
			else
				continue;
		}
		add_history(line);
		write(open, line, ft_strlen(line));
		free(line);
	}
	return (open);
}
