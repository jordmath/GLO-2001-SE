#include <stdio.h>
#include <pthread.h> 
//gcc ThreadVariableShare.c -o ThreadVariableShare -pthread

//int compteur = 0;   // variable partagée entre threads

void* thread(void* arg) {
    int* compteur = (int*)arg;   // on récupère l’adresse partagée
    (*compteur)++;               // modification visible par tous les threads
    return NULL;
}

//Version correcte (avec mutex) — juste pour comparaison
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void* thread2(void* arg) {
    pthread_mutex_lock(&m);
    int* compteur = (int*)arg;   // on récupère l’adresse partagée
    (*compteur)++;               // modification visible par tous les threads
    pthread_mutex_unlock(&m);
    return NULL;
}

int main() {
    int compteur = 0;   // variable LOCALE à main
    pthread_t t1, t2;

    pthread_create(&t1, NULL, thread, &compteur);
    pthread_create(&t2, NULL, thread, &compteur);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Valeur finale de compteur = %d\n", compteur);

    return 0;
}
