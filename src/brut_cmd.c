/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brut_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 11:28:08 by hbray             #+#    #+#             */
/*   Updated: 2026/03/24 15:00:46 by hbray            ###   ########.fr       */
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
	uptade_env(&env, "PDW", new_path);
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
