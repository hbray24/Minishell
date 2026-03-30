/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 16:12:33 by asauvage          #+#    #+#             */
/*   Updated: 2026/03/30 18:09:17 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#include <stdio.h>

void print_string_array(char **array, const char *name, int depth)
{
    if (!array || !array[0])
        return;
    
    for (int i = 0; i < depth; i++)
        printf("    ");
    printf("|- %s : [", name);
    for (int i = 0; array[i] != NULL; i++)
    {
        printf("\"%s\"", array[i]);
        if (array[i + 1] != NULL)
            printf(", ");
    }
    printf("]\n");
}

void print_ast(t_ast *node, int depth)
{
    if (!node)
        return;

    for (int i = 0; i < depth; i++)
        printf("    ");
    printf("NODE (Type: %d)\n", node->type);
    print_string_array(node->token, "Tokens", depth);
    print_string_array(node->files, "Files", depth);
    print_string_array(node->fd, "FDs", depth);
    print_string_array(node->limiter, "Limiters", depth);
    if (node->l_child)
    {
        for (int i = 0; i < depth; i++) printf("    ");
        printf("|- Left:\n");
        print_ast(node->l_child, depth + 1);
    }
    
    if (node->r_child)
    {
        for (int i = 0; i < depth; i++) printf("    ");
        printf("|- Right:\n");
        print_ast(node->r_child, depth + 1);
    }
}

int	parse(t_token *token, t_env *env)
{
	t_ast *ast;
	t_token	*token_tmp;
	int	status;
	(void)env;
	(void)token;

	status = 1;
	token_tmp = last_token(&token);
	ast = parsing(token_tmp);
	print_ast(ast, 0);
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
