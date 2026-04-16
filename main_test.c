/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 13:33:47 by asauvage          #+#    #+#             */
/*   Updated: 2026/04/16 14:03:01 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <unistd.h>

int	main(int ac, char **av)
{
	char	*line;
	int		i;

	i = 0;
	(void)ac;
	while (av && av[i])
	{
		line = readline(">");
		if (!line)
		{
			perror("Minishell");
			return (1);
		}
		printf("%d\n", i);
		if (!strcmp(line, av[i]))
		{
			i++;
			continue;
		}
		add_history(line);
		free(line);
	}
	return (0);
}
