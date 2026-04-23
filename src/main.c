/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 16:12:33 by asauvage          #+#    #+#             */
/*   Updated: 2026/04/23 10:38:02 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parse(t_token **token, t_env **env)
{
	t_ast	*ast;
	int		status;

	if (!expander(*token, *env))
	{
		status = 1;
		return ;
	}
	ast = parsing(last_token(token));
	if (!ast)
	{
		ast->status = 1;
		return ;
	}
	clear_token(token);
	ignore_signal();
	status = exec_ast(ast, env, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	clear_ast(&ast);
	(*env)->status = status;
	restore_signal();
}

int	check_line(char *line, t_token **token, t_env **env)
{
	if (!line)
		ft_exit(NULL, *env);
	*token = malloc_struct();
	if (ft_strlen(line) == 0)
	{
		free(line);
		return (0);
	}
	add_history(line);
	if (lexer(line, *token))
	{
		free(line);
		return (1);
	}
	free(line);
	parse(token, env);
	clear_token(token);
	return (0);
}

void	minishell_loop(t_env **env)
{
	char	*line;
	t_token	*token;

	token = NULL;
	while (1)
	{
		gestion_term(0);
		line = readline("minishell> ");
		gestion_term(1);
		if (g_signal_status)
		{
			(*env)->status = g_signal_status;
			g_signal_status = 0;
		}
		if (check_line(line, &token, env) == 1)
			break ;
	}
	clear_token(&token);
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;

	(void)av;
	if (ac != 1)
		return (1);
	gestion_term(1);
	init_signal();
	env = init_env(envp);
	minishell_loop(&env);
	rl_clear_history();
	clear_env(&env);
	return (0);
}
