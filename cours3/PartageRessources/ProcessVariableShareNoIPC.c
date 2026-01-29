#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int compteur = 0;   // variable locale n'est pas partagé

    pid_t pid = fork();

    if (pid == 0) {
        // FILS
        compteur++;
        printf("Fils : compteur = %d\n", compteur);
        _exit(0);
    } else {
        // PÈRE
        wait(NULL);
        printf("Père : compteur = %d\n", compteur);
    }

    return 0;
}

