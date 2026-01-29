#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define REP 100
#define DELAY 10000000

// Fonction pour afficher une lettre plusieurs fois
void afficher(char lettre) {
    int i, j;
    for (j = 1; j <= REP; j++) {
        for (i = 1; i < DELAY; i++);  // boucle de retard
        printf("%c", lettre);
        fflush(stdout);
    }
}

// Fonction thread
void *thread(void *plettre) {
    char lettre = *(char *)plettre;  // récupère la lettre
    afficher(lettre);
    printf("\nFin du thread %c\n", lettre);
    pthread_exit(NULL);
}

int main() {
    pthread_t thA, thB, thC;

    printf("Creation des threads A et B\n");
    char lettreA = 'A';
    char lettreB = 'B';
    //pthread_create(&thA, NULL, thread, &lettreA);
    pthread_create(&thA, NULL, thread, "A"); // 'A': error
    
    //"A" est une chaine de caractere et En C, une chaîne est un tableau stocké en mémoire. Donc "A" est adresse valide en mémoire
    //'A' est un caractère, pas une adresse // Sa valeur numérique est 65
    //Le thread va interpréter 65 comme une adresse mémoire : comportement indéfini / segfault
    pthread_create(&thB, NULL, thread, &lettreB);

    // attendre la fin des threads A et B
    printf("Le thread principal attend la fin des threads A et B\n");
    pthread_join(thA, NULL);
    pthread_join(thB, NULL);

    printf("\nCreation du thread C\n");
    char lettreC = 'C';
    pthread_create(&thC, NULL, thread, &lettreC);

    printf("Le thread principal attend la fin du thread C\n");
    pthread_join(thC, NULL);

    printf("Tous les threads ont termine.\n");
    return 0;
}

