/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 13:10:21 by asauvage          #+#    #+#             */
/*   Updated: 2026/05/02 16:30:01 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_all(t_token **token, t_env **env, t_ast **ast)
{
	clear_token(token);
	clear_ast(ast);
	clear_env(env);
}

void	free_array(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str && str[i])
		free(str[i++]);
	free(str);
}

void	clear_token(t_token **token)
{
	t_token	*tmp;

	if (!token || !(*token))
		return ;
	while (*token)
	{
		free((*token)->token);
		tmp = *token;
		*token = (*token)->next;
		free(tmp);
	}
	*token = NULL;
}

void	clear_env(t_env **env)
{
	t_env	*tmp;

	if (!env || !(*env))
		return ;
	while (*env)
	{
		free((*env)->key);
		free((*env)->value);
		tmp = *env;
		*env = (*env)->next;
		free(tmp);
	}
	*env = NULL;
}

void	clear_ast(t_ast **ast)
{
	if (!ast || !(*ast))
		return ;
	free_array((*ast)->token);
	free_array((*ast)->files);
	free_array((*ast)->limiter);
	free((*ast)->redir);
	if ((*ast)->fd[0] > -1)
		close((*ast)->fd[0]);
	if ((*ast)->fd[0] > -1)
		close((*ast)->fd[0]);
	if ((*ast)->l_child)
		clear_ast(&(*ast)->l_child);
	if ((*ast)->r_child)
		clear_ast(&(*ast)->r_child);
	free(*ast);
	*ast = NULL;
}
