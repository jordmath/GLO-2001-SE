#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int compteur = 0;   //  PAS partagé entre processus
    int fd[2];

    pipe(fd);           // fd[0] = lecture, fd[1] = écriture

    pid_t pid = fork();

    if (pid == 0) {
        // ----- FILS -----
        close(fd[0]);           // fils ferme lecture
        compteur++;                 // modifie SA copie
        write(fd[1], &compteur, sizeof(compteur));
        _exit(0);
    } else {
        // ----- PÈRE -----
        close(fd[1]);           // père doit fermer écriture !
        wait(NULL);
        read(fd[0], &compteur, sizeof(compteur));
        printf("Valeur finale du compteur = %d\n", compteur);
    }

    return 0;
}
