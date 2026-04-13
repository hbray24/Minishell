/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 16:12:33 by asauvage          #+#    #+#             */
/*   Updated: 2026/04/13 20:06:52 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	parse(t_token **token, t_env **env)
{
	t_ast	*ast;
	t_token	*token_tmp;
	int		status;

	expander(*token, *env);
	token_tmp = last_token(token);
	ast = parsing(token_tmp);
	clear_token(token);
	status = exec_ast(ast, env, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
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
	{
		return (1);
	}
	clear_token(token);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_token	*token;
	t_env	*env;
	// int		save_stdin;
	// int		save_stdout;

	(void)av;
	if (ac != 1)
		return (1);
	env = init_env(envp);
	token = NULL;
	// save_stdin = dup(STDIN_FILENO);
	// save_stdout = dup(STDOUT_FILENO);
	while (1)
	{
		// dup2(save_stdin, STDIN_FILENO);
		// dup2(save_stdout, STDOUT_FILENO);
		line = readline("minishell> ");
		if (check_line(line, &token, &env) == 1)
			break ;
	}
	rl_clear_history();
	clear_token(&token);
	clear_env(&env);
	return (0);
}
