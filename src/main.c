/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 16:12:33 by asauvage          #+#    #+#             */
/*   Updated: 2026/04/15 16:53:45 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_signal_status;

void	manages_signal(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		g_signal_status = 130;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
 	{
		printf("\n");
		rl_on_new_line();
		g_signal_status = 131;
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	parse(t_token **token, t_env **env)
{
	t_ast	*ast;
	int		status;

	if (!expander(*token, *env))
	{
		status = 1;
		return ;
	}
	ast = parsing(last_token(token));
	if (!ast)
	{
		ast->status = 1;
		return ;
	}
	status = exec_ast(ast, env, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	clear_ast(&ast);
	(*env)->status = status;
}

int	check_line(char *line, t_token **token, t_env **env)
{
	if (!line)
	{
		printf("exit\n");
		return (1);
	}
	*token = malloc_struct();
	if (ft_strlen(line) == 0)
	{
		free(line);
		return (0);
	}
	add_history(line);
	if (lexer(line, *token))
	{
		free(line);
		return (1);
	}
	free(line);
	parse(token, env);
	clear_token(token);
	return (0);
}

void	masque_caractere(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO,&term) == -1)
	{
		perror("tcgettattr");
		return;
	}
	term.c_cc[VQUIT] = _POSIX_VDISABLE;
	if(tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		perror("tcsetattr");
}

int	main(int ac, char **av, char **envp)
{
	struct sigaction	sig_action;
	char	*line;
	t_token	*token;
	t_env	*env;

	(void)av;
	if (ac != 1)
		return (1);
	sigemptyset(&sig_action.sa_mask);
	sigaddset(&sig_action.sa_mask, SIGINT);
	sigaddset(&sig_action.sa_mask, SIGQUIT);
	sig_action.sa_handler = manages_signal;
	sig_action.sa_flags = 0;
	sigaction(SIGINT, &sig_action, NULL);
	sigaction(SIGQUIT, &sig_action, NULL);
	env = init_env(envp);
	token = NULL;
	while (1)
	{
		// if (!g_signal_status)
		// {
		// 	env->status = g_signal_status;
		// 	g_signal_status = 0;
		// }
		line = readline("minishell> ");
		masque_caractere();

		if (check_line(line, &token, &env) == 1)
			break ;
	}
	rl_clear_history();
	clear_token(&token);
	clear_env(&env);
	return (0);
}
