#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid;

    printf("Avant fork() : PID = %d\n", getpid());

    pid = fork();   // création du processus enfant
    printf("PID  = %d\n", pid);
    

    if (pid < 0) {
        // Erreur : fork a échoué (seul le parent arrive ici)
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        // Code exécuté par le processus enfant
        printf("  Processus ENFANT\n");
        printf("  PID enfant = %d\n", getpid());
        printf("  PID parent = %d\n", getppid());
        
        exit(0);
    }
    else {
        // Code exécuté par le processus parent
        printf("  Processus PARENT\n");
        printf("  PID parent = %d\n", getpid());
        printf("  PID enfant = %d\n", pid);
        wait(0);
    }

    printf("Fin du processus PID = %d\n", getpid());
    return 0;
}
