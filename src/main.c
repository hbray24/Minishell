/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 16:12:33 by asauvage          #+#    #+#             */
/*   Updated: 2026/03/24 16:17:53 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <minishell.h>

void	parse(t_token *token, t_env *env)
{
	if (ft_strcmp(token->token, "cd") == 0)
		ft_cd(token, env);
	else if (ft_strcmp(token->token, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(token->token, "env") == 0)
		ft_env(&env);
	return ;
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
		parse(token, env);
		clear_token(&token);
		free(line);
	}
	return (0);
}
