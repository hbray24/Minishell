/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 16:12:33 by asauvage          #+#    #+#             */
/*   Updated: 2026/03/31 15:24:38 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	parse(t_token *token, t_env *env)
{
	t_ast	*ast;
	t_token	*token_tmp;
	int		status;

	(void)env;
	(void)token;
	status = 1;
	token_tmp = last_token(&token);
	ast = parsing(token_tmp);
	//status = exec_ast(ast);
	// print_ast(ast, 0);
	// if (ft_strcmp(token->token, "cd") == 0)
	// 	status |= ft_cd(token, env);
	// else if (ft_strcmp(token->token, "pwd") == 0)
	// 	status |= ft_pwd();
	// else if (ft_strcmp(token->token, "env") == 0)
	// 	ft_env(&env);
	// else if (ft_strcmp(token->token, "exit") == 0)
	// {
	// 	clear_ast(&ast);
	// 	return (0);
	// }
	clear_ast(&ast);
	return (status);
}

int	cacaboudin(char *line, t_token *token, t_env *env)
{
	if (!line)
	{
		printf("exit\n");
		return (1);
	}
	token = malloc_struct();
	if (ft_strlen(line) == 0)
	{
		free(line);
		clear_token(&token);
		return (0);
	}
	add_history(line);
	if (lexer(line, token))
	{
		free(line);
		clear_token(&token);
		rl_clear_history();
		exit(1);
	}
	free(line);
	if (!parse(token, env))
		return (1);
	clear_token(&token);
	return (0);
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
		if (cacaboudin(line, token, env) == 1)
			break ;
	}
	rl_clear_history();
	clear_token(&token);
	clear_env(&env);
	return (0);
}
