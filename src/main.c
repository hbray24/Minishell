/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 16:12:33 by asauvage          #+#    #+#             */
/*   Updated: 2026/03/24 14:50:14 by asauvage         ###   ########.fr       */
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

	while ((line = readline("minishell> ")) != NULL)
	{
		token = malloc_struct();
		if (ft_strlen(line) > 0)
			add_history(line);
		if (lexer(line, token))
		{
			free(line);
			clear_token(&token);
			return (1);
		}
		clear_token(&token);
		free(line);
	}
	return (0);
}
