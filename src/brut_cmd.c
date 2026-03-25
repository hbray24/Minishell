/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brut_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 11:28:08 by hbray             #+#    #+#             */
/*   Updated: 2026/03/25 11:07:50 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_token *token, t_env *env)
{
	char	*old_path;
	char	*new_path;

	old_path = getcwd(NULL, 0);
	if (!old_path)
		return (0);
	if (chdir(token->next->token) == -1)
	{
		perror("hbray: cd");
		free(old_path);
		return (0);
	}
	new_path = getcwd(NULL, 0);
	if (!new_path)
	{
		free(old_path);
		return (0);
	}
	uptade_env(&env, "OLDPWD", old_path);
	uptade_env(&env, "PWD", new_path);
	free(old_path);
	free(new_path);
	return (1);
}

int	ft_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		perror("hbray: ");
		return (0);
	}
	printf("%s\n", path);
	free(path);
	return (1);
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
