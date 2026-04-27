/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 10:25:44 by hbray             #+#    #+#             */
/*   Updated: 2026/04/27 10:30:03 by hbray            ###   ########.fr       */
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

int	check_quote_limiter(char **str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\'' || (*str)[i] == '\"')
		{
			if (delete_quote(str) == -1)
				return (2);
			return (1);
		}
		i++;
	}
	return (0);
}
