/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 16:12:33 by asauvage          #+#    #+#             */
/*   Updated: 2026/04/14 15:27:46 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	parse(t_token **token, t_env **env)
{
	t_ast	*ast;
	int		status;

	if (!expander(*token, *env))
	{
		ast->status = 1;
		return ;
	}
	ast = parsing(last_token(token));
	if (!ast)
	{
		ast->status = 1;
		return ;
	}
	status = exec_ast(ast, env, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	clear_ast(&ast);
	(*env)->status = status;
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
		return (1);
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
