/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zebi_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 18:27:17 by asauvage          #+#    #+#             */
/*   Updated: 2026/04/13 19:06:38 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

// --- STRUCTURES MINIMALISTES ---
typedef enum e_type { PIPE, EXEC } t_type;

typedef struct s_ast {
    t_type          type;
    char            **cmd;      // Tableau d'arguments (ex: {"ls", "-l", NULL})
    struct s_ast    *l_child;
    struct s_ast    *r_child;
} t_ast;

// --- FONCTION À CODER ---
// C'est ici que tu dois appliquer la logique récursive
int execute_ast(t_ast *ast)
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipe_ast[2];
	int		status_gauche;
	int		status_droite;
    // TON CODE ICI
    
    // Si ast->type == PIPE : pipe(), fork gauche, fork droit, close, waitpid...
	if (ast->type == PIPE)
	{
		pipe(pipe_ast);
		pid1 = fork();
		if (pid1 == 0)
		{
			dup2(pipe_ast[1], 1);
			close(pipe_ast[1]);
			close(pipe_ast[0]);
			execute_ast(ast->l_child);
			exit (1);
		}
		pid2 = fork();
		if (pid2 == 0)
		{
			dup2(pipe_ast[0], 0);
			close(pipe_ast[1]);
			close(pipe_ast[0]);
			execute_ast(ast->r_child);
			exit (1);
		}
		close(pipe_ast[0]);
		close(pipe_ast[1]);
		waitpid(pid1, &status_gauche, 0);
		waitpid(pid2, &status_droite, 0);
		return (status_droite);
	}
    // Si ast->type == EXEC : execvp(ast->cmd[0], ast->cmd)
	if (ast->type == EXEC)
		execvp(ast->cmd[0], ast->cmd);
	perror("Error exec");
	exit (127);
    // Note : pour cet exercice, utilise execvp au lieu de execve, 
    // ça t'évitera de devoir coder la récupération du PATH.
}

// --- UTILITAIRES POUR L'EXERCICE (Ne pas modifier) ---
t_ast *create_exec_node(char **cmd)
{
    t_ast *node = malloc(sizeof(t_ast));
    node->type = EXEC;
    node->cmd = cmd;
    node->l_child = NULL;
    node->r_child = NULL;
    return node;
}

t_ast *create_pipe_node(t_ast *left, t_ast *right)
{
    t_ast *node = malloc(sizeof(t_ast));
    node->type = PIPE;
    node->cmd = NULL;
    node->l_child = left;
    node->r_child = right;
    return node;
}

int main(void)
{
    // Simulation de la commande :  ls -la | grep "c" | wc -l
    // L'arbre généré est associatif à gauche :
    //        PIPE_1
    //       /      \
    //   PIPE_2     EXEC(wc -l)
    //   /    \
    // EXEC(ls) EXEC(grep c)

    char *cmd1[] = {"ls", "-la", NULL};
    char *cmd2[] = {"grep", "c", NULL};
    char *cmd3[] = {"wc", "-l", NULL};

    t_ast *node_ls = create_exec_node(cmd1);
    t_ast *node_grep = create_exec_node(cmd2);
    t_ast *node_wc = create_exec_node(cmd3);

    t_ast *pipe_2 = create_pipe_node(node_ls, node_grep);
    t_ast *pipe_1 = create_pipe_node(pipe_2, node_wc);

    printf("Début de l'exécution de l'AST...\n");
    
    execute_ast(pipe_1);
    
    printf("\nExécution terminée. Si tout est correct, tu devrais voir le même chiffre qu'en tapant 'ls -la | grep c | wc -l' dans ton terminal.\n");

    return (0);
}