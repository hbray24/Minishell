/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 11:04:32 by asauvage          #+#    #+#             */
/*   Updated: 2026/05/01 17:42:19 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _DEFAULT_SOURCE

# include "../libft/libft.h"
# include <dirent.h>
# include <errno.h>
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
	int				origin_std[2];
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
	struct s_ast	**first_node_ast;
}					t_env;

extern int			g_signal_status;

t_token				*malloc_struct(void);
t_token				*last_token(t_token **token);
t_token				*first_token(t_token *token);
t_token				*search_pipe(t_token *tokens);
t_env				*init_env(char **envp);
t_env				*swap_node(t_env *env, t_env *env_cmp);
t_env				*create_env_node(char *key, char *value);
t_ast				*parsing(t_token *token);
t_ast				*new_ast_node(void);
pid_t				fork_pipe_child(t_ast *ast, t_env **env, int fd_pipe[2],
						int direction);
char				**split(char *str);
char				**del_null_str(char **cmd, int *i);
char				*search_value(char *key, t_env *env);
char				*get_value(char *str);
char				*get_key(char *str);
char				*find_cmd_path(char *cmd, char **envp);
char				*search_old_path(t_env *env);
char				*search_new_path(t_ast *ast, char *old_path);
char				*search_value(char *key, t_env *env);
char				*search_variable(char *str, t_env *env);
char				*search_key(char *key, t_env *env);
char				*alloc_new_str(int len);
char				*realloc_token(char *str, int start, int len_var,
						char *value);
char				*expand_env_var(char *str, t_env *env, int *i);
char				*new_status(char *str, t_env *env, int flags, int *i);
char				*remove_quote(char **str, char *res);
void				clear_token(t_token **token);
void				free_array(char **str);
void				clear_env(t_env **env);
void				clear_ast(t_ast **ast);
void				ft_unset(t_ast *ast, t_env **env);
void				ft_echo(t_ast *ast);
void				close_fd(t_ast *ast);
void				ignore_signal(void);
void				restore_signal(void);
void				init_signal(void);
void				manages_signal(int sig);
void				restore_fd(int origin_stdout_in[2]);
void				init_signal_heredoc(void);
void				signal_heredoc(int sig);
void				free_all(t_token **token, t_env **env, t_ast **ast);
void				close_std_fd(void);
int					atollong(char *str, t_env *env);
int					gestion_term(int action);
int					close_pipe(int fd_pipe[2]);
int					add_env(t_env **env_list, t_env *new_node);
int					ft_export(t_ast *ast, t_env **env);
int					ft_env(t_ast *ast, t_env **env);
int					expander(char **cmd, t_env *env);
int					expander_simple_array(char **str, t_env *env);
int					uptade_env(t_env **env, char *key, char *new_value);
int					add_node(t_token *token, char *str, int type);
int					lexer(char *str, t_token *token, t_env **env);
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
int					here_doc(t_ast *ast, char **limiter, t_env *env);
int					dup_fd(t_ast *ast);
int					exec_no_fork(t_ast *ast, t_env **env);
int					get_exit_status(int status);
int					dup2_child(t_ast *ast, t_env **env, int fd_pipe[2],
						int direction);
int					check_fd(t_ast *ast, t_env *env);
int					single_or_double_q(char **str);
int					delete_quote(char **str);
int					count_redir(t_token *token);
int					open_file(char **tmp);
int					check_quote_limiter(char **str);
int					check_nb_quote(char *str);

#endif