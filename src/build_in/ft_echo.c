/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 10:13:28 by hbray             #+#    #+#             */
/*   Updated: 2026/04/08 11:36:52 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_flags(char *str)
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

void	ft_echo_with_flags(t_ast *ast)
{
	int	i;

	i = 2;
		while (ast->token[i])
		{
			if (check_flags(ast->token[i]) == 1)
				break;
			i++;
		}
		while (ast->token[i])
		{
			printf("%s", ast->token[i]);
			if (ast->token[i + 1] != NULL)
				printf(" ");
			i++;
		}
}

void	ft_echo_without_flags(t_ast *ast)
{
	int	i;

	i = 1;
	while (ast->token[i])
	{
		printf("%s", ast->token[i]);
		if (ast->token[i + 1] != NULL)
			printf(" ");
		i++;
	}
	printf("\n");
}

void	ft_echo(t_ast *ast)
{
	if (check_flags(ast->token[1]) == 0)
		ft_echo_with_flags(ast);
	else
		ft_echo_without_flags(ast);
}
