/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 16:12:33 by asauvage          #+#    #+#             */
/*   Updated: 2026/03/25 11:09:18 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	parse(t_token *token, t_env *env)
{
	int	status;

	status = 1;
	if (ft_strcmp(token->token, "cd") == 0)
		status |= ft_cd(token, env);
	else if (ft_strcmp(token->token, "pwd") == 0)
		status |= ft_pwd();
	else if (ft_strcmp(token->token, "env") == 0)
		ft_env(&env);
	else if (ft_strcmp(token->token, "exit") == 0)
		return (0);
	return (status);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_token	*token;
	t_env	*env;

	(void)ac;
	(void)av;
	env = init_env(envp);
	token = malloc_struct();
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
		free(line);
		if (!parse(token, env))
		{
			clear_token(&token);
			break ;
		}
		clear_token(&token);
	}
	clear_env(&env);
	return (0);
}
