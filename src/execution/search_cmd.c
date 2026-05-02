/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 13:31:33 by hbray             #+#    #+#             */
/*   Updated: 2026/05/02 16:53:55 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*strcat_path_cmd(char *dst, char *src)
{
	int		i;
	int		j;
	char	*res;
	int		len;

	len = ft_strlen(dst) + ft_strlen(src) + 2;
	res = malloc(sizeof(char) * (len));
	if (!res)
		return (perror("Minishell"), NULL);
	i = 0;
	while (src[i])
	{
		res[i] = src[i];
		i++;
	}
	res[i++] = '/';
	j = 0;
	while (dst[j])
		res[i++] = dst[j++];
	res[i] = '\0';
	return (res);
}

char	**find_env(char **envp)
{
	int		i;
	char	**path;

	i = -1;
	path = NULL;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_split(&envp[i][5], ':');
			break ;
		}
	}
	if (!path)
	{
		perror("Minishell :find_env");
		return (NULL);
	}
	return (path);
}

char	*search_in_path(char *cmd, char **path)
{
	int		i;
	char	*tmp;

	i = -1;
	while (path[++i])
	{
		tmp = strcat_path_cmd(cmd, path[i]);
		if (!tmp)
			return (NULL);
		if (!access(tmp, X_OK))
			return (tmp);
		free(tmp);
	}
	return (NULL);
}

char	*find_cmd_path(char *cmd, char **envp)
{
	char	*tmp;
	char	**path;

	if (cmd[0] == '\0')
		return (NULL);
	if (!access(cmd, X_OK))
	{
		tmp = ft_strdup(cmd);
		if (!tmp)
		{
			perror("Minishell :find_cmd_path");
			return (NULL);
		}
		return (tmp);
	}
	path = find_env(envp);
	if (!path)
		return (NULL);
	tmp = search_in_path(cmd, path);
	free_array(path);
	return (tmp);
}
