/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 16:12:33 by asauvage          #+#    #+#             */
/*   Updated: 2026/04/08 20:45:50 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	parse(t_token **token, t_env **env)
{
	t_ast	*ast;
	t_pipe	pipe;
	t_token	*token_tmp;
	int		status;

	pipe.pipes = NULL;
	pipe.nb_pipe = 0;
	expander(*token, *env);
	token_tmp = last_token(token);
	ast = parsing(token_tmp);
	if (ast->type == PIPE)
		pipe.pipes = 0;
	clear_token(token);
	if (!malloc_pipe(ast, &pipe))
		return (0);
	status = execute_ast(ast, env, &pipe, pipe.nb_pipe);
	clear_ast(&ast);
	return (status);
}

int	check_line(char *line, t_token **token, t_env **env)
{
	if (!line)
	{
		printf("exit\n");
		return (1);
	}
	*token = malloc_struct();
	if (ft_strlen(line) == 0)
	{
		free(line);
		clear_token(token);
		return (0);
	}
	add_history(line);
	if (lexer(line, *token))
	{
		free(line);
		clear_token(token);
		rl_clear_history();
		exit(1);
	}
	free(line);
	if (parse(token, env))
		return (1);
	clear_token(token);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_token	*token;
	t_env	*env;

	(void)av;
	if (ac != 1)
		return (1);
	env = init_env(envp);
	token = NULL;
	while (1)
	{
		line = readline("minishell> ");
		if (check_line(line, &token, &env) == 1)
			break ;
	}
	rl_clear_history();
	clear_token(&token);
	clear_env(&env);
	return (0);
}


/*Force toi rien a redire fin de journee avec mal de crane comprends pas inshallah
tu commences la journee tres joyeusement car la ca va etre dure je te le dis ca va 
barabara. En vrai regarde bien la partie de comment se creer les pipes les dup2
redirection et tout sur pipe files tout ca....*/