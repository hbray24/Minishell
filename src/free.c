/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 13:10:21 by asauvage          #+#    #+#             */
/*   Updated: 2026/04/07 15:50:21 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **str)
{
	int	i;

	i = 0;
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
	clear_ast(&(*ast)->l_child);
	clear_ast(&(*ast)->r_child);
	free(*ast);
	*ast = NULL;
}
