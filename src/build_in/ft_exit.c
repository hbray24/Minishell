/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 16:28:32 by asauvage          #+#    #+#             */
/*   Updated: 2026/05/01 17:41:45 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	close_std_fd(void)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
}

int	error(char *str, t_env *env)
{
	write(2, "Minishell: exit: ", 18);
	ft_putstr_fd(str, 2);
	write(2, ": numeric argument required\n", 29);
	env->status = 2;
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

int	atollong(char *str, t_env *env)
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
			return (error(str, env));
		nb = nb * 10 + str[i++] - '0';
	}
	if (str[i])
		return (error(str, env));
	env->status = ((long long)nb * m) % 256;
	return (0);
}

int	ft_exit(t_ast *ast, t_env *env)
{
	int	status;

	status = 0;
	write(1, "exit\n", 5);
	if (ast && ast->token[1])
	{
		if (!atollong(ast->token[1], env) && ast->token[2])
		{
			write(2, "Minishell: exit: too many arguments\n", 37);
			return (1);
		}
	}
	if (ast)
		restore_fd(ast->origin_std);
	status = env->status;
	clear_ast(env->first_node_ast);
	clear_env(&env);
	rl_clear_history();
	close_std_fd();
	exit(status);
}
