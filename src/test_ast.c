#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_node
{
	int				val;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

typedef struct s_expr
{
	char			op;
	int				val;
	struct s_expr	*left;
	struct s_expr	*right;
}	t_expr;

typedef enum e_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_REDIR_IN,
	NODE_REDIR_OUT,
	NODE_REDIR_APPEND,
	NODE_REDIR_HEREDOC
}	t_type;

typedef struct s_ast
{
	t_type			type;
	char			**token;
	struct s_ast	*l_child;
	struct s_ast	*r_child;
}	t_ast;

t_node	*new_node(int val)
{
	t_node	*n;
	n = malloc(sizeof(t_node));
	n->val = val; n->left = NULL; n->right = NULL;
	return (n);
}

t_expr	*new_leaf(int val)
{
	t_expr	*n;
	n = malloc(sizeof(t_expr));
	n->op = '\0'; n->val = val; n->left = NULL; n->right = NULL;
	return (n);
}

t_expr	*new_op(char op)
{
	t_expr	*n;
	n = malloc(sizeof(t_expr));
	n->op = op; n->val = 0; n->left = NULL; n->right = NULL;
	return (n);
}

t_ast	*new_ast_node(t_type type)
{
	t_ast	*n;
	n = malloc(sizeof(t_ast));
	n->type = type; n->token = NULL;
	n->l_child = NULL; n->r_child = NULL;
	return (n);
}

static void	build_prefix(const char *prefix, int is_left, char *out)
{
	int	i = 0;
	while (prefix[i]) { out[i] = prefix[i]; i++; }
	if (is_left) { out[i++]='|'; out[i++]=' '; out[i++]=' '; out[i++]=' '; }
	else         { out[i++]=' '; out[i++]=' '; out[i++]=' '; out[i++]=' '; }
	out[i] = '\0';
}

void	print_node(t_node *n, const char *prefix, int is_left)
{
	char np[256];
	if (!n) return;
	printf("%s%s%d\n", prefix, is_left ? "+-- " : "\\-- ", n->val);
	build_prefix(prefix, is_left, np);
	print_node(n->left, np, 1); print_node(n->right, np, 0);
}
void	show_tree(t_node *root)
{
	if (!root) { printf("  (vide)\n"); return; }
	printf("  %d\n", root->val);
	print_node(root->left, "", 1); print_node(root->right, "", 0);
}

void	print_expr(t_expr *n, const char *prefix, int is_left)
{
	char np[256];
	if (!n) return;
	if (n->op) printf("%s%s'%c'\n", prefix, is_left?"+-- ":"\\-- ", n->op);
	else       printf("%s%s%d\n",   prefix, is_left?"+-- ":"\\-- ", n->val);
	build_prefix(prefix, is_left, np);
	print_expr(n->left, np, 1); print_expr(n->right, np, 0);
}
void	show_expr(t_expr *root)
{
	if (!root) { printf("  (vide)\n"); return; }
	if (root->op) printf("  '%c'\n", root->op);
	else          printf("  %d\n",   root->val);
	print_expr(root->left, "", 1); print_expr(root->right, "", 0);
}

static const char	*type_str(t_type t)
{
	if (t == NODE_CMD)          return ("CMD");
	if (t == NODE_PIPE)         return ("PIPE");
	if (t == NODE_REDIR_IN)     return ("REDIR_IN");
	if (t == NODE_REDIR_OUT)    return ("REDIR_OUT");
	if (t == NODE_REDIR_APPEND) return ("REDIR_APPEND");
	return ("HEREDOC");
}

void	print_ast(t_ast *n, const char *prefix, int is_left)
{
	char	np[256];
	int		i;
	if (!n) return;
	printf("%s%s[%s]", prefix, is_left?"+-- ":"\\-- ", type_str(n->type));
	if (n->token) { i=0; while(n->token[i]) printf(" %s", n->token[i++]); }
	printf("\n");
	build_prefix(prefix, is_left, np);
	print_ast(n->l_child, np, 1); print_ast(n->r_child, np, 0);
}
void	show_ast(t_ast *root)
{
	int	i;
	if (!root) { printf("  (vide)\n"); return; }
	printf("  [%s]", type_str(root->type));
	if (root->token) { i=0; while(root->token[i]) printf(" %s", root->token[i++]); }
	printf("\n");
	print_ast(root->l_child, "", 1); print_ast(root->r_child, "", 0);
}

void	free_tree(t_node *n) { if(!n)return; free_tree(n->left); free_tree(n->right); free(n); }
void	free_expr(t_expr *n) { if(!n)return; free_expr(n->left); free_expr(n->right); free(n); }
void	free_ast(t_ast *n)
{
	int i;
	if (!n) return;
	if (n->token) { i=0; while(n->token[i]) free(n->token[i++]); free(n->token); }
	free_ast(n->l_child); free_ast(n->r_child); free(n);
}

#define SEP "-------------------------------------------"
#define HDR(t) printf("\n[ %s ]\n%s\n", t, SEP)
#define CHECK(got, exp) printf("  Resultat : %d  (attendu : %d)  %s\n\n", \
	got, exp, (got)==(exp)?"OK":"ERREUR")

/* ===== EXERCICE 2 ===== */

t_node	*build_bst(int *arr, int start, int end)
{
	int		mid;
	t_node	*node;
	if (start > end) return (NULL);
	mid = (start + end) / 2;
	node = new_node(arr[mid]);
	node->left  = build_bst(arr, start, mid - 1);
	node->right = build_bst(arr, mid + 1, end);
	return (node);
}

void	test_ex2(void)
{
	printf("\n==========================================\n");
	printf("     EXERCICE 2 : build_bst\n");
	printf("==========================================\n");

	HDR("Test A : {1,2,3,4,5} -> racine=3");
	{ int arr[]={1,2,3,4,5}; t_node *t=build_bst(arr,0,4); show_tree(t);
	  printf("  Racine      : %d  (attendu : 3)  %s\n", t->val, t->val==3?"OK":"ERREUR");
	  printf("  Fils gauche : %d  (attendu : 1)  %s\n", t->left->val, t->left->val==1?"OK":"ERREUR");
	  printf("  Fils droit  : %d  (attendu : 4)  %s\n\n", t->right->val, t->right->val==4?"OK":"ERREUR");
	  free_tree(t); }

	HDR("Test B : {10,20,30} -> racine=20");
	{ int arr[]={10,20,30}; t_node *t=build_bst(arr,0,2); show_tree(t);
	  printf("  Racine : %d  (attendu : 20)  %s\n\n", t->val, t->val==20?"OK":"ERREUR");
	  free_tree(t); }

	HDR("Test C : {42} -> noeud seul");
	{ int arr[]={42}; t_node *t=build_bst(arr,0,0); show_tree(t);
	  printf("  Racine : %d  (attendu : 42)    %s\n", t->val, t->val==42?"OK":"ERREUR");
	  printf("  left   : %s  (attendu : NULL)  %s\n\n", t->left?"non-NULL":"NULL", !t->left?"OK":"ERREUR");
	  free_tree(t); }

	HDR("Test D : {1..7} -> arbre complet, racine=4");
	{ int arr[]={1,2,3,4,5,6,7}; t_node *t=build_bst(arr,0,6); show_tree(t);
	  printf("  Racine : %d  (attendu : 4)  %s\n\n", t->val, t->val==4?"OK":"ERREUR");
	  free_tree(t); }
}

/* ===== EXERCICE 3 ===== */

int	find_op(char **tok, int start, int end, char *ops)
{
	int i = end;
	while (i >= start)
	{
		if (tok[i][1]=='\0' && strchr(ops, tok[i][0])) return (i);
		i--;
	}
	return (-1);
}

t_expr	*parse_expr(char **tok, int start, int end)
{
	int		idx;
	t_expr	*node;
	idx = find_op(tok, start, end, "+-");
	if (idx == -1) idx = find_op(tok, start, end, "*/");
	if (idx == -1) return (new_leaf(atoi(tok[start])));
	node = new_op(tok[idx][0]);
	node->left  = parse_expr(tok, start, idx - 1);
	node->right = parse_expr(tok, idx + 1, end);
	return (node);
}

void	test_ex3(void)
{
	printf("\n==========================================\n");
	printf("     EXERCICE 3 : parse_expr\n");
	printf("==========================================\n");

	HDR("Test A : \"3 + 5 * 2\" -> racine='+'");
	{ char *tok[]={"3","+","5","*","2",NULL}; t_expr *t=parse_expr(tok,0,4); show_expr(t);
	  printf("  Racine : '%c'  (attendu : '+')  %s\n\n", t->op, t->op=='+'?"OK":"ERREUR");
	  free_expr(t); }

	HDR("Test B : \"10 * 2 + 3\" -> racine='+'");
	{ char *tok[]={"10","*","2","+","3",NULL}; t_expr *t=parse_expr(tok,0,4); show_expr(t);
	  printf("  Racine : '%c'  (attendu : '+')  %s\n\n", t->op, t->op=='+'?"OK":"ERREUR");
	  free_expr(t); }

	HDR("Test C : \"6 / 2 / 3\" -> assoc. gauche");
	{ char *tok[]={"6","/","2","/","3",NULL}; t_expr *t=parse_expr(tok,0,4); show_expr(t);
	  printf("  Racine : '%c'  (attendu : '/')  %s\n", t->op, t->op=='/'?"OK":"ERREUR");
	  printf("  Fils g : '%c'  (attendu : '/')  %s\n\n", t->left->op, t->left->op=='/'?"OK":"ERREUR");
	  free_expr(t); }

	HDR("Test D : \"7\" -> feuille seule");
	{ char *tok[]={"7",NULL}; t_expr *t=parse_expr(tok,0,0); show_expr(t);
	  printf("  val : %d  (attendu : 7)  %s\n\n", t->val, t->val==7?"OK":"ERREUR");
	  free_expr(t); }
}

/* ===== EXERCICE 4 ===== */

int	eval(t_expr *node)
{
	if (node->op=='+') return(eval(node->left)+eval(node->right));
	if (node->op=='-') return(eval(node->left)-eval(node->right));
	if (node->op=='*') return(eval(node->left)*eval(node->right));
	if (node->op=='/') return(eval(node->left)/eval(node->right));
	return(node->val);
}

void	test_ex4(void)
{
	printf("\n==========================================\n");
	printf("     EXERCICE 4 : eval\n");
	printf("==========================================\n");

	HDR("Test A : \"3 + 5 * 2\" -> 13");
	{ char *tok[]={"3","+","5","*","2",NULL}; t_expr *t=parse_expr(tok,0,4); show_expr(t); CHECK(eval(t),13); free_expr(t); }
	HDR("Test B : \"10 - 2 - 3\" -> 5");
	{ char *tok[]={"10","-","2","-","3",NULL}; t_expr *t=parse_expr(tok,0,4); show_expr(t); CHECK(eval(t),5); free_expr(t); }
	HDR("Test C : \"2 * 3 + 4 * 5\" -> 26");
	{ char *tok[]={"2","*","3","+","4","*","5",NULL}; t_expr *t=parse_expr(tok,0,6); show_expr(t); CHECK(eval(t),26); free_expr(t); }
	HDR("Test E : \"42\" -> 42");
	{ char *tok[]={"42",NULL}; t_expr *t=parse_expr(tok,0,0); show_expr(t); CHECK(eval(t),42); free_expr(t); }
}

/* ===== EXERCICE 5 — fonctions de l'etudiant ===== */

int	search_pipe(char **tokens, int start, int end)
{
	int	i = end;
	while (i >= start)
	{
		if (tokens[i][0] == '|') return (i);
		i--;
	}
	return (-1);
}

int	search_redir(char **tokens, int start, int end)
{
	int	i = end;
	while (i >= start)
	{
		if (!strcmp(tokens[i],"<<") || !strcmp(tokens[i],"<")
			|| !strcmp(tokens[i],">") || !strcmp(tokens[i],">>"))
			return (i);
		i--;
	}
	return (-1);
}

t_ast	*check_redir(char *token)
{
	if (!strcmp(token, "<"))  return (new_ast_node(NODE_REDIR_IN));
	if (!strcmp(token, "<<")) return (new_ast_node(NODE_REDIR_HEREDOC));
	if (!strcmp(token, ">"))  return (new_ast_node(NODE_REDIR_OUT));
	if (!strcmp(token, ">>")) return (new_ast_node(NODE_REDIR_APPEND));
	return (NULL);
}

char	**sub_strstr(char **str, int start, int end)
{
	char	**res;
	int		i = 0;
	res = malloc(sizeof(char *) * (end - start + 2));
	while (start <= end) res[i++] = strdup(str[start++]);
	res[i] = NULL;
	return (res);
}

t_ast	*build_ast(char **tokens, int start, int end)
{
	t_ast	*ast;
	int		i;

	i = search_pipe(tokens, start, end);
	if (i != -1)
	{
		ast = new_ast_node(NODE_PIPE);
		ast->l_child = build_ast(tokens, start, i - 1);
		ast->r_child = build_ast(tokens, i + 1, end);
		return (ast);
	}
	i = search_redir(tokens, start, end);
	if (i != -1)
	{
		ast = check_redir(tokens[i]);
		ast->l_child = build_ast(tokens, start, i - 1);
		ast->token = malloc(sizeof(char *) * 2);
		ast->token[0] = strdup(tokens[i + 1]);
		ast->token[1] = NULL;
	}
	else
	{
		ast = new_ast_node(NODE_CMD);
		ast->token = sub_strstr(tokens, start, end);
	}
	return (ast);
}

/* ===== TESTS EXERCICE 5 — option B ===== */

void	test_ex5(void)
{
	printf("\n==========================================\n");
	printf("     EXERCICE 5 : build_ast (option B)\n");
	printf("==========================================\n");

	/*
	** Option B : les redirections sont des noeuds dans l'arbre.
	** Le fichier est stocke dans token[0] du noeud redir.
	** l_child = ce qui est a gauche de la redir (la commande ou redir precedente)
	** r_child = NULL (le fichier est dans token[0], pas recurse)
	**
	** Exemple : cat < in.txt > out.txt
	**
	**   [REDIR_OUT] out.txt      <- racine (redir la plus a droite)
	**   +-- [REDIR_IN] in.txt   <- l_child
	**       +-- [CMD] cat       <- l_child du REDIR_IN
	*/

	HDR("Test A : \"ls -la\" -> CMD seul");
	/*
	**   [CMD] ls -la
	*/
	{
		char	*tok[] = {"ls", "-la", NULL};
		t_ast	*t = build_ast(tok, 0, 1);
		show_ast(t);
		printf("  racine   : %s  (attendu : CMD)  %s\n",
			type_str(t->type), t->type==NODE_CMD?"OK":"ERREUR");
		printf("  token[0] : %s  (attendu : ls)   %s\n",
			t->token[0], !strcmp(t->token[0],"ls")?"OK":"ERREUR");
		printf("  token[1] : %s  (attendu : -la)  %s\n\n",
			t->token[1], !strcmp(t->token[1],"-la")?"OK":"ERREUR");
		free_ast(t);
	}

	HDR("Test B : \"ls | grep foo\" -> PIPE(CMD ls, CMD grep)");
	/*
	**   [PIPE]
	**   +-- [CMD] ls
	**   \-- [CMD] grep foo
	*/
	{
		char	*tok[] = {"ls", "|", "grep", "foo", NULL};
		t_ast	*t = build_ast(tok, 0, 3);
		show_ast(t);
		printf("  racine      : %s  (attendu : PIPE)  %s\n",
			type_str(t->type), t->type==NODE_PIPE?"OK":"ERREUR");
		printf("  fils gauche : %s  (attendu : CMD)   %s\n",
			type_str(t->l_child->type), t->l_child->type==NODE_CMD?"OK":"ERREUR");
		printf("  fils droit  : %s  (attendu : CMD)   %s\n\n",
			type_str(t->r_child->type), t->r_child->type==NODE_CMD?"OK":"ERREUR");
		free_ast(t);
	}

	HDR("Test C : \"cat < in.txt\" -> REDIR_IN(CMD cat)");
	/*
	**   [REDIR_IN] in.txt    <- racine, token[0]="in.txt"
	**   +-- [CMD] cat        <- l_child
	*/
	{
		char	*tok[] = {"cat", "<", "in.txt", NULL};
		t_ast	*t = build_ast(tok, 0, 2);
		show_ast(t);
		printf("  racine         : %s  (attendu : REDIR_IN)  %s\n",
			type_str(t->type), t->type==NODE_REDIR_IN?"OK":"ERREUR");
		printf("  token[0]       : %s  (attendu : in.txt)    %s\n",
			t->token[0], !strcmp(t->token[0],"in.txt")?"OK":"ERREUR");
		printf("  l_child type   : %s  (attendu : CMD)       %s\n",
			type_str(t->l_child->type), t->l_child->type==NODE_CMD?"OK":"ERREUR");
		printf("  l_child token  : %s  (attendu : cat)       %s\n\n",
			t->l_child->token[0], !strcmp(t->l_child->token[0],"cat")?"OK":"ERREUR");
		free_ast(t);
	}

	HDR("Test D : \"cat < in.txt > out.txt\" -> REDIR_OUT(REDIR_IN(CMD cat))");
	/*
	**   [REDIR_OUT] out.txt       <- racine (redir la plus a droite)
	**   +-- [REDIR_IN] in.txt     <- l_child
	**       +-- [CMD] cat         <- l_child du REDIR_IN
	*/
	{
		char	*tok[] = {"cat", "<", "in.txt", ">", "out.txt", NULL};
		t_ast	*t = build_ast(tok, 0, 4);
		show_ast(t);
		printf("  racine              : %s  (attendu : REDIR_OUT)  %s\n",
			type_str(t->type), t->type==NODE_REDIR_OUT?"OK":"ERREUR");
		printf("  token[0]            : %s  (attendu : out.txt)    %s\n",
			t->token[0], !strcmp(t->token[0],"out.txt")?"OK":"ERREUR");
		printf("  l_child type        : %s  (attendu : REDIR_IN)   %s\n",
			type_str(t->l_child->type), t->l_child->type==NODE_REDIR_IN?"OK":"ERREUR");
		printf("  l_child token[0]    : %s  (attendu : in.txt)     %s\n",
			t->l_child->token[0], !strcmp(t->l_child->token[0],"in.txt")?"OK":"ERREUR");
		printf("  l_child->l_child    : %s  (attendu : CMD)        %s\n\n",
			type_str(t->l_child->l_child->type),
			t->l_child->l_child->type==NODE_CMD?"OK":"ERREUR");
		free_ast(t);
	}

	HDR("Test E : \"ls | cat < in.txt\" -> PIPE(CMD ls, REDIR_IN(CMD cat))");
	/*
	**   [PIPE]
	**   +-- [CMD] ls
	**   \-- [REDIR_IN] in.txt
	**       +-- [CMD] cat
	*/
	{
		char	*tok[] = {"ls", "|", "cat", "<", "in.txt", NULL};
		t_ast	*t = build_ast(tok, 0, 4);
		show_ast(t);
		printf("  racine           : %s  (attendu : PIPE)     %s\n",
			type_str(t->type), t->type==NODE_PIPE?"OK":"ERREUR");
		printf("  fils gauche      : %s  (attendu : CMD)      %s\n",
			type_str(t->l_child->type), t->l_child->type==NODE_CMD?"OK":"ERREUR");
		printf("  fils droit       : %s  (attendu : REDIR_IN) %s\n",
			type_str(t->r_child->type), t->r_child->type==NODE_REDIR_IN?"OK":"ERREUR");
		printf("  r_child token[0] : %s  (attendu : in.txt)  %s\n",
			t->r_child->token[0], !strcmp(t->r_child->token[0],"in.txt")?"OK":"ERREUR");
		printf("  r_child->l_child : %s  (attendu : CMD)     %s\n\n",
			type_str(t->r_child->l_child->type),
			t->r_child->l_child->type==NODE_CMD?"OK":"ERREUR");
		free_ast(t);
	}

	HDR("Test F : \"echo hello >> log.txt\" -> REDIR_APPEND(CMD echo)");
	/*
	**   [REDIR_APPEND] log.txt
	**   +-- [CMD] echo hello
	*/
	{
		char	*tok[] = {"echo", "hello", ">>", "log.txt", NULL};
		t_ast	*t = build_ast(tok, 0, 3);
		show_ast(t);
		printf("  racine       : %s  (attendu : REDIR_APPEND)  %s\n",
			type_str(t->type), t->type==NODE_REDIR_APPEND?"OK":"ERREUR");
		printf("  token[0]     : %s  (attendu : log.txt)       %s\n",
			t->token[0], !strcmp(t->token[0],"log.txt")?"OK":"ERREUR");
		printf("  l_child      : %s  (attendu : CMD)           %s\n",
			type_str(t->l_child->type), t->l_child->type==NODE_CMD?"OK":"ERREUR");
		printf("  l_child tok0 : %s  (attendu : echo)          %s\n\n",
			t->l_child->token[0], !strcmp(t->l_child->token[0],"echo")?"OK":"ERREUR");
		free_ast(t);
	}

	HDR("Test G : \"cat < in.txt | grep foo | wc -l > out.txt\"");
	/*
	**   [PIPE]
	**   +-- [REDIR_IN] in.txt
	**   |   +-- [CMD] cat
	**   \-- [PIPE]
	**       +-- [CMD] grep foo
	**       \-- [REDIR_APPEND] out.txt
	**           +-- [CMD] wc -l
	*/
	{
		char	*tok[] = {
			"cat", "<", "in.txt", "|",
			"grep", "foo", "|",
			"wc", "-l", ">", "out.txt", NULL
		};
		t_ast	*t = build_ast(tok, 0, 10);
		show_ast(t);
		printf("  racine          : %s  (attendu : PIPE)     %s\n",
			type_str(t->type), t->type==NODE_PIPE?"OK":"ERREUR");
		printf("  fils gauche     : %s  (attendu : PIPE)      %s\n",
			type_str(t->l_child->type), t->l_child->type==NODE_PIPE?"OK":"ERREUR");
		printf("  fils droit      : %s  (attendu : REDIR_OUT) %s\n",
			type_str(t->r_child->type), t->r_child->type==NODE_REDIR_OUT?"OK":"ERREUR");
		printf("  l->l (cat redir): %s  (attendu : REDIR_IN)  %s\n",
			type_str(t->l_child->l_child->type),
			t->l_child->l_child->type==NODE_REDIR_IN?"OK":"ERREUR");
		printf("  l->r (grep)     : %s  (attendu : CMD)       %s\n\n",
			type_str(t->l_child->r_child->type),
			t->l_child->r_child->type==NODE_CMD?"OK":"ERREUR");
		free_ast(t);
	}
}

int	main(int ac, char **av)
{
	(void)av;
	if (ac == 2) test_ex2();
	if (ac == 3) test_ex3();
	if (ac == 4) test_ex4();
	if (ac == 5) test_ex5();
	printf("\n=== Tous les tests termines ===\n\n");
	return (0);
}