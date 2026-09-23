#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>


#define TOTAL_PUNTOS 100000000
#define NUM_HILOS 16

int puntosDentro = 0;

sem_t semaforo;

void *monteCarlo(void *arg)
{
    for (int i = 0; i < (TOTAL_PUNTOS / NUM_HILOS); i++)
    {
        double x = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
        double y = ((double)rand() / RAND_MAX) * 2.0 - 1.0;

        if (x * x + y * y <= 1.0)
        {
            sem_wait(&semaforo);

            puntosDentro++;

            sem_post(&semaforo);
        }
    }

    return NULL;
}

int main(void){
clock_t inicio = clock();

pthread_t hilo1, hilo2, hilo3, hilo4, hilo5, hilo6, hilo7, hilo8, hilo9, hilo10, hilo11, hilo12, hilo13, hilo14, hilo15, hilo16;

    sem_init(&semaforo, 0, 1);

    pthread_create(&hilo1, NULL, monteCarlo, NULL);
    pthread_create(&hilo2, NULL, monteCarlo, NULL);
    pthread_create(&hilo3, NULL, monteCarlo, NULL);
    pthread_create(&hilo4, NULL, monteCarlo, NULL);
    pthread_create(&hilo5, NULL, monteCarlo, NULL);
    pthread_create(&hilo6, NULL, monteCarlo, NULL);
    pthread_create(&hilo7, NULL, monteCarlo, NULL);
    pthread_create(&hilo8, NULL, monteCarlo, NULL);
    pthread_create(&hilo9, NULL, monteCarlo, NULL);
    pthread_create(&hilo10, NULL, monteCarlo, NULL);
    pthread_create(&hilo11, NULL, monteCarlo, NULL);
    pthread_create(&hilo12, NULL, monteCarlo, NULL);
    pthread_create(&hilo13, NULL, monteCarlo, NULL);
    pthread_create(&hilo14, NULL, monteCarlo, NULL);
    pthread_create(&hilo15, NULL, monteCarlo, NULL);
    pthread_create(&hilo16, NULL, monteCarlo, NULL);

    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);
    pthread_join(hilo3, NULL);
    pthread_join(hilo4, NULL);
    pthread_join(hilo5, NULL);
    pthread_join(hilo6, NULL);
    pthread_join(hilo7, NULL);
    pthread_join(hilo8, NULL);
    pthread_join(hilo9, NULL);
    pthread_join(hilo10, NULL);
    pthread_join(hilo11, NULL);
    pthread_join(hilo12, NULL);
    pthread_join(hilo13, NULL);
    pthread_join(hilo14, NULL);
    pthread_join(hilo15, NULL);
    pthread_join(hilo16, NULL);

    double pi = 4.0 * puntosDentro / TOTAL_PUNTOS;

    printf("Puntos totales: %d\n", TOTAL_PUNTOS);
    printf("Puntos dentro: %d\n", puntosDentro);
    printf("Aproximacion de Pi: %f\n", pi);


    clock_t fin = clock();
    double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;

    printf("Tiempo de CPU: %f segundos\n",tiempo);

    sem_destroy(&semaforo);

    return 0;
}