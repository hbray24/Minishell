/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 16:12:59 by asauvage          #+#    #+#             */
/*   Updated: 2026/04/03 15:12:30 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
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
}					t_type;

typedef struct s_ast
{
	char			**token;
	int				*fd;
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
	t_type			type;
	struct s_token	*next;
	struct s_token	*pre;
}					t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*pre;
}					t_env;

t_token				*malloc_struct(void);
t_token				*last_token(t_token **token);
t_token				*first_token(t_token *token);
t_env				*init_env(char **envp);
t_env				*swap_node(t_env *env, t_env *env_cmp);
char				**split(char *str);
char				*search_value(char *key, t_env *env);
char				*get_value(char *str);
char				*get_key(char *str);
void				clear_token(t_token **token);
void				free_array(char **str);
void				uptade_env(t_env **env, char *key, char *new_value);
void				clear_env(t_env **env);
void				clear_ast(t_ast **ast);
void				ft_env(t_env **env);
void				ft_unset(t_ast *ast, t_env **env);
void				ft_export(t_ast *ast, t_env **env);
int					add_node(t_token *token, char *str, int type);
int					lexer(char *str, t_token *token);
int					skip_w_quote(char *str, int i);
int					ft_issep(char *str, int *i, int index_go);
int					ft_cd(t_ast *ast, t_env *env);
int					ft_pwd(void);
int					create_token(t_token *token);
int					execute_ast(t_ast *ast, t_env *envp);
int					add_node_env(t_env **env, char *key, char *value);
int					is_valid(char *str);
t_ast				*parsing(t_token *token);
t_ast				*new_ast_node(void);

#endif