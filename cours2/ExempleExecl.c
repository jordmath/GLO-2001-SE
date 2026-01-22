#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Processus fils
        printf("Fils : exécution de ls -l\n");

        //execl("/bin/ls", "ls", "-l", NULL);
        execlp("ls", "ls", "-la", NULL);
        
        //execl("/home/etu1//cours/cours2/ProcessInitialData", "ProcessInitialData", NULL);
        //execl("./ProcessInitialData", "ProcessInitialData", NULL);
	//execlp("ProcessInitialData", "ProcessInitialData", NULL); // Mettre le binaire dans un répertoire du $PATH

        // Cette ligne ne s'exécute que si execl échoue
        perror("execl");
        return 1;
    } else {
        // Processus père
        printf("Père : attente du fils...\n");
        wait(NULL);
        printf("Père : fin du fils\n");
    }

    return 0;
}

