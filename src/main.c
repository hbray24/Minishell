/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 16:12:33 by asauvage          #+#    #+#             */
/*   Updated: 2026/03/23 18:44:10 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// int	find_substr(char *find, char *str)
// {
// 	int	i;
// 	int	j;
// 	int	len;
// 	int	len_str;

// 	i = 0;
// 	len_str = ft_strlen(str);
// 	len = ft_strlen(find);
// 	while (str && str[i] && i < len_str - len)
// 	{
// 		j = 0;
// 		while (j < len && find[j++] == str[i++]);
// 		if (j == len)
// 			return (1);
// 		i = i - j + 1;
// 	}
// 	return (0);
// }

// char	*find_pwd(char **str)
// {
// 	int	i;

// 	i = 0;
// 	while (str && str[i])
// 	{
// 		if (find_substr("PWD=", str[i]))
// 			return (&str[i][4]);
// 		i++;
// 	}
// 	return (NULL);
// }

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;
	char	*line;
	t_token	*token;

	token = malloc_struct();
	while ((line = readline("minishell> ")) != NULL)
	{
		if (ft_strlen(line) > 0)
			add_history(line);
		if (lexer(line, token))
		{
			free(line);
			return (1);
		}
		free(line);
	}
	return (0);
}
