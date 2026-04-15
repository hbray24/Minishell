/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 10:13:28 by hbray             #+#    #+#             */
/*   Updated: 2026/04/15 19:04:48 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_option(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
	{
		i++;
		while (str[i] == 'n')
			i++;
		if (str[i] == '\0')
			return(0);
	}
	return (1);
}

void	ft_echo_with_option(t_ast *ast)
{
	int	i;

	i = 2;
		while (ast->token[i])
		{
			if (check_option(ast->token[i]) == 1)
				break;
			i++;
		}
		while (ast->token[i])
		{
			ft_putstr_fd(ast->token[i], 1);
			if (ast->token[i + 1] != NULL)
				ft_putstr_fd(" ", 1);
			i++;
		}
}

void	ft_echo_without_option(t_ast *ast)
{
	int	i;

	i = 1;
	while (ast->token[i])
	{
		ft_putstr_fd(ast->token[i], 1);
		if (ast->token[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
	ft_putstr_fd("\n", 1);
}

void	ft_echo(t_ast *ast)
{
	if (check_option(ast->token[1]) == 0)
		ft_echo_with_option(ast);
	else
		ft_echo_without_option(ast);
}
