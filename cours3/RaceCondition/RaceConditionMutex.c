#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N_THREADS 20
#define N_INCREMENTS 1000
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

int compteur = 0;   // donnée partagée



void* thread(void* arg) {
    for (int i = 0; i < N_INCREMENTS; i++) {
        pthread_mutex_lock(&m);
        int tmp = compteur;   // lire
        //usleep(1);            // fenêtre critique
        compteur = tmp + 1;   // écrire
        pthread_mutex_unlock(&m);
    }
    return NULL;
}

int main() {
    pthread_t t[N_THREADS];

    for (int i = 0; i < N_THREADS; i++)
        pthread_create(&t[i], NULL, thread, NULL);

    for (int i = 0; i < N_THREADS; i++)
        pthread_join(t[i], NULL);

    printf("Sans mutex : compteur = %d (attendu = %d)\n",
           compteur, N_THREADS * N_INCREMENTS);
}

