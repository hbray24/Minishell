/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 16:12:59 by asauvage          #+#    #+#             */
/*   Updated: 2026/04/22 14:57:00 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _DEFAULT_SOURCE

# include "../libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <unistd.h>

typedef enum s_type
{
	WORD,
	FILES,
	LIMITER,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_ADD,
	HERE_DOC,
	SINGLE_Q,
	DOUBLE_Q,
	EXEC,
	RIGHT,
	LEFT,
}					t_type;

typedef struct s_ast
{
	int				fd[2];
	int				status;
	char			**token;
	char			**files;
	char			**limiter;
	t_type			*redir;
	t_type			type;
	struct s_ast	*l_child;
	struct s_ast	*r_child;
}					t_ast;

typedef struct s_token
{
	char			*token;
	int				limite;
	int				was_quote;
	t_type			type;
	struct s_token	*next;
	struct s_token	*pre;
}					t_token;

typedef struct s_env
{
	char			**env;
	char			*key;
	char			*value;
	int				status;
	struct s_env	*next;
	struct s_env	*pre;
}					t_env;

extern int			g_signal_status;

t_token				*malloc_struct(void);
t_token				*last_token(t_token **token);
t_token				*first_token(t_token *token);
t_token				*search_pipe(t_token *tokens);
t_env				*init_env(char **envp);
t_env				*swap_node(t_env *env, t_env *env_cmp);
t_ast				*parsing(t_token *token);
t_ast				*new_ast_node(void);
pid_t				fork_pipe_child(t_ast *ast, t_env **env, int fd_pipe[2],
						int direction);
char				**split(char *str);
char				*search_value(char *key, t_env *env);
char				*get_value(char *str);
char				*get_key(char *str);
char				*find_cmd_path(char *cmd, char **envp);
char				*search_old_path(t_env *env);
char				*search_new_path(t_ast *ast, char *old_path);
char				*search_value(char *key, t_env *env);
char				*search_key(char *key, t_env *env);
char				*alloc_new_str(int len);
void				clear_token(t_token **token);
void				free_array(char **str);
void				clear_env(t_env **env);
void				clear_ast(t_ast **ast);
void				ft_unset(t_ast *ast, t_env **env);
void				ft_echo(t_ast *ast);
void				close_fd(t_ast *ast);
void				gestion_term(int action);
void				ignore_signal(void);
void				restore_signal(void);
void				init_signal(void);
void				manages_signal(int sig);
void				restore_fd(int origin_stdout_in[2]);
void				close_pipe(int fd_pipe[2]);
long long			atollong(char *str);
int				ft_export(t_ast *ast, t_env **env);
int					ft_env(t_ast *ast, t_env **env);
int					expander(t_token *token, t_env *env);
int					uptade_env(t_env **env, char *key, char *new_value);
int					add_node(t_token *token, char *str, int type);
int					lexer(char *str, t_token *token);
int					skip_w_quote(char *str, int i);
int					ft_issep(char *str, int *i, int index_go);
int					ft_cd(t_ast *ast, t_env *env);
int					ft_pwd(void);
int					exec_ast(t_ast *ast, t_env **env, int create_fork);
int					add_node_env(t_env **env, char *key, char *value);
int					is_valid(char *str);
int					ft_exit(t_ast *ast, t_env *env);
int					execve_cmd(t_ast *ast, t_env **env);
int					exec_build_in(t_ast *ast, t_env **env);
int					create_token(t_token *token);
int					here_doc(t_ast *ast, char *limiter);
int					dup_fd(t_ast *ast);
int					exec_no_fork(t_ast *ast, t_env **env);
int					get_exit_status(int status);
int					dup2_child(t_ast *ast, t_env **env, int fd_pipe[2],
						int direction);
int					check_fd(t_ast *ast);
int					single_or_double_q(char **str);
int					delete_quote(char **str);
int					count_redir(t_token *token);

#endif