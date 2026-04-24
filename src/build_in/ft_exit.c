/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 16:28:32 by asauvage          #+#    #+#             */
/*   Updated: 2026/04/24 11:19:10 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	error(char *str)
{
	ft_putstr_fd("Hbray: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric arguments required", 2);
	return (2);
}

int	check_limit_nb(unsigned long long res, int new_nb, int m)
{
	if (m == 1)
	{
		if (res > LLONG_MAX / 10 || (res == LLONG_MAX / 10 && new_nb > 7))
			return (1);
	}
	else
	{
		if (res > LLONG_MAX / 10 || (res == LLONG_MAX / 10 && new_nb > 8))
			return (1);
	}
	return (0);
}

long long	atollong(char *str)
{
	unsigned long long	nb;
	int					m;
	int					i;

	i = 0;
	m = 1;
	nb = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			m = -1;
	}
	while (ft_isdigit(str[i]))
	{
		if (check_limit_nb(nb, (str[i] - '0'), m))
			return (error(str));
		nb = nb * 10 + str[i++] - '0';
	}
	if (str[i])
		return (error(str));
	return ((long long)nb * m);
}

int	ft_exit(t_ast *ast, t_env *env)
{
	int	status;

	status = 0;
	write(1, "exit\n", 5);
	if (ast && ast->token[1])
	{
		if (ast->token[2])
		{
			write(2, "Minishell: exit: too many arguments\n", 37);
			return (1);
		}
		env->status = atollong(ast->token[1]) % 256;
	}
	status = env->status;
	clear_env(&env);
	clear_ast(&ast);
	rl_clear_history();
	exit(status);
}
