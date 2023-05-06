#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv) {
    char *dir = argv[1];
    if (dir == NULL) {
        // si aucun chemin n'est fourni, utilisez le répertoire personnel de l'utilisateur
        dir = getenv("HOME");
    }

    if (chdir(dir) != 0) {
        // Si l'opération de changement de répertoire a échoué
        if (errno == EACCES) {
            printf("cd: accès refusé\n");
        } else if (errno == ENOENT) {
            printf("cd: chemin introuvable\n");
        } else {
            printf("cd: erreur inconnue\n");
        }
    }

    char *cwd = getcwd(NULL, 0);
    if (cwd == NULL) {
        printf("cd: erreur lors de la récupération du répertoire de travail courant\n");
    } else {
        // Mettre à jour la variable d'environnement PWD
        setenv("PWD", cwd, 1);
        printf("%s\n", cwd);
        free(cwd);
    }

    return 0;
}
