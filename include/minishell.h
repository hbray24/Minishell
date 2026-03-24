/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 16:12:59 by asauvage          #+#    #+#             */
/*   Updated: 2026/03/24 15:12:51 by asauvage         ###   ########.fr       */
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
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_ADD,
	HERE_DOC,
}					t_type;

typedef struct s_token
{
	char			*token;
	t_type			type;
	struct s_token	*next;
	struct s_token	*pre;
}					t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

t_token				*malloc_struct(void);
char				**split(char *str);
void				free_array(char **str);
int					lexer(char *str, t_token *token);
void				clear_token(t_token **token);
int					add_node(t_token *token, char *str, int type);
t_token				*last_token(t_token *token);
t_token				*first_token(t_token *token);
int					skip_w_quote(char *str, int i);
int					ft_issep(char *str, int *i, int index_go);
void				ft_cd(t_token *token, t_env *env);
void				uptade_env(t_env **env, char *key, char *new_value);
t_env				*init_env(char **envp);
void				ft_pwd(void);

#endif