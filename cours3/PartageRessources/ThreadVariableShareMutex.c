#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // pour usleep
#define N_THREADS 10
#define INCREMENTS 1000

void* thread(void* arg) {
    int* compteur = (int*)arg;
    for(int i=0; i<INCREMENTS; i++) {
        int tmp = *compteur;  // lire la valeur
        usleep(1);            // pause très courte pour forcer le chevauchement
        tmp++;                // incrément
        *compteur = tmp;      // écrire
    }
    return NULL;
}

// Version correcte avec mutex
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
void* thread2(void* arg) {
    int* compteur = (int*)arg;
    for(int i=0; i<INCREMENTS; i++) {
        pthread_mutex_lock(&m);
        (*compteur)++;
        pthread_mutex_unlock(&m);
    }
    return NULL;
}

int main() {
    int compteur = 0;
    pthread_t t[N_THREADS];

    // Threads sans mutex
    for(int i=0; i<N_THREADS; i++)
        pthread_create(&t[i], NULL, thread, &compteur);
    for(int i=0; i<N_THREADS; i++)
        pthread_join(t[i], NULL);

    printf("Sans mutex : compteur final = %d (attendu = %d)\n",
           compteur, N_THREADS*INCREMENTS);

    // Threads avec mutex
    compteur = 0;
    for(int i=0; i<N_THREADS; i++)
        pthread_create(&t[i], NULL, thread2, &compteur);
    for(int i=0; i<N_THREADS; i++)
        pthread_join(t[i], NULL);

    printf("Avec mutex : compteur final = %d (attendu = %d)\n",
           compteur, N_THREADS*INCREMENTS);

    return 0;
}

