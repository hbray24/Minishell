/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:40:01 by hbray             #+#    #+#             */
/*   Updated: 2026/04/15 10:35:10 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_ast *ast, t_env **env)
{
	t_env	*current_env;

	if (ast->token[1] != NULL)
	{
		write (2, "env : '", 8);
		write (2, ast->token[1], ft_strlen(ast->token[1]));
		write (2, "': No such file or directory\n", 30);
		return (127);
	}
	current_env = *env;
	while (current_env)
	{
		if (current_env->value != NULL)
			printf("%s=%s\n", current_env->key, current_env->value);
		current_env = current_env->next;
	}
	return (0);
}
