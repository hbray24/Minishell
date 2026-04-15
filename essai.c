#include <termios.h>
#include <unistd.h>
#include <stdio.h>

void masquer_caracteres_controle() {
    struct termios term;

    // 1. On récupère la configuration actuelle du terminal lié à l'entrée standard (le clavier)
    if (tcgetattr(STDIN_FILENO, &term) == -1) {
        perror("tcgetattr");
        return;
    }

    // 2. On modifie les "flags" locaux (c_lflag) pour désactiver ECHOCTL
    // ECHOCTL gère l'affichage de ^C, ^Z, ^\ etc.
    term.c_lflag &= ~ECHOCTL;

    // 3. On applique la nouvelle configuration immédiatement (TCSANOW)
    if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1) {
        perror("tcsetattr");
    }
}

int main() {
    // On appelle la fonction au tout début du minishell
    masquer_caracteres_controle();

    printf("Minishell prêt. Fais Ctrl-Z ou Ctrl-C : plus rien ne s'affiche !\n");

    while(1) {
        sleep(1);
    }

    return 0;
}