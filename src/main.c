/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 16:12:33 by asauvage          #+#    #+#             */
/*   Updated: 2026/05/02 17:34:36 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parse(t_token **token, t_env **env)
{
	t_ast	*ast;
	int		status;

	ast = parsing(last_token(token));
	if (!ast)
	{
		(*env)->status = 1;
		return ;
	}
	clear_token(token);
	ignore_signal();
	(*env)->first_node_ast = &ast;
	status = fill_here_doc(ast, *env);
	if (status == -1)
		return (free_all(token, env, (*env)->first_node_ast), exit(1));
	if (status == -3)
		return (clear_ast((*env)->first_node_ast));
	status = exec_ast(ast, env, 0);
	if (status == -1)
		return (free_all(token, env, (*env)->first_node_ast), exit(1));
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	clear_ast((*env)->first_node_ast);
	(*env)->status = status;
	restore_signal();
}

void	check_line(char *line, t_token **token, t_env **env)
{
	if (!line)
		ft_exit(NULL, *env);
	*token = malloc_struct();
	if (!token || !*token)
		return (free(line));
	if (ft_strlen(line) == 0)
	{
		free(line);
		clear_token(token);
		return ;
	}
	add_history(line);
	if (lexer(line, *token, env))
	{
		free(line);
		clear_token(token);
		return ;
	}
	free(line);
	parse(token, env);
	clear_token(token);
	(*env)->first_node_ast = NULL;
	return ;
}

void	minishell_loop(t_env **env)
{
	char	*line;
	t_token	*token;

	token = NULL;
	while (1)
	{
		if (!gestion_term(0))
			return ;
		line = readline("minishell$ ");
		if (!gestion_term(1))
			return ;
		if (g_signal_status)
		{
			(*env)->status = g_signal_status;
			g_signal_status = 0;
		}
		check_line(line, &token, env);
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
	if (!env)
		return (1);
	minishell_loop(&env);
	rl_clear_history();
	clear_env(&env);
	return (0);
}
