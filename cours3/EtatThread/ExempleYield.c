//#define _GNU_SOURCE // est un macro de préprocesseur qui active les extensions GNU dans les fichiers d’en-tête de la libc (glibc).
//ça débloque des fonctions non standard POSIX
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sched.h>

void* thread(void* arg) {
    char* nom = (char*)arg;

    for (int i = 0; i < 5; i++) {
        printf("Thread %s : %d\n", nom, i);
        //pthread_yield();   // cède volontairement le CPU
        sched_yield(); 
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, thread, "A");
    pthread_create(&t2, NULL, thread, "B");

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
