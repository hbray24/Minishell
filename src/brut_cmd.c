/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brut_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 11:28:08 by hbray             #+#    #+#             */
/*   Updated: 2026/03/25 10:44:29 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_token *token, t_env *env)
{
	char	*old_path;
	char	*new_path;

	old_path = getcwd(NULL, 0);
	if (!old_path)
		return;
	if (chdir(token->next->token) == -1)
	{
		perror("hbray: cd");
		free(old_path);
		return;
	}
	new_path = getcwd(NULL, 0);
	if (!new_path)
	{
		free(old_path);
		return;
	}
	uptade_env(&env, "OLDPWD", old_path);
	uptade_env(&env, "PWD", new_path);
	free(old_path);
	free(new_path);
}

void	ft_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		perror("asauvage: ");
		return;
	}
	printf("%s\n", path);
	free(path);
}

void	ft_env(t_env **env)
{
	t_env	*current_env;

	current_env = *env;
	while (current_env)
	{
		printf("%s=", current_env->key);
		printf("%s\n", current_env->value);
		current_env = current_env->next;
	}
}
