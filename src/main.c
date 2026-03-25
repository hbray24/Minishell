/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 16:12:33 by asauvage          #+#    #+#             */
/*   Updated: 2026/03/25 14:21:31 by asauvage         ###   ########.fr       */
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

int	main(int ac, char **envp)
{
	char	*line;
	t_token	*token;
	t_env	*env;

	if (ac != 1)
		return (1);
	env = init_env(envp);
	token = NULL;
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		token = malloc_struct();
		if (ft_strlen(line) == 0)
		{
			free(line);
			clear_token(&token);
			continue ;
		}
		add_history(line);
		if (lexer(line, token))
		{
			free(line);
			clear_token(&token);
			rl_clear_history();
			return (1);
		}
		free(line);
		if (!parse(token, env))
			break ;
		clear_token(&token);
	}
	rl_clear_history();
	clear_token(&token);
	clear_env(&env);
	return (0);
}
