/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 13:31:33 by hbray             #+#    #+#             */
/*   Updated: 2026/04/08 14:14:58 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strcat_path_cmd(char *dst, char *src)
{
	int		i;
	int		j;
	char	*res;
	int		len;

	len = ft_strlen(dst) + ft_strlen(src) + 2;
	res = malloc(sizeof(char) * (len));
	if (!res)
		return (0);
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
	return (path);
}

char	*find_cmd_path(char *cmd, char **envp)
{
	int		i;
	char	*tmp;
	char	**path;

	if (!access(cmd, X_OK))
		return (ft_strdup(cmd));
	i = -1;
	path = find_env(envp);
	if (!path)
		return (NULL);
	tmp = cmd;
	i = -1;
	while (path[++i])
	{
		tmp = strcat_path_cmd(cmd, path[i]);
		if (!access(tmp, X_OK))
		{
			free_array(path);
			return (tmp);
		}
		free(tmp);
	}
	free_array(path);
	return (NULL);
}
