#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define TOTAL_PUNTOS 100000000
#define NUM_HILOS 2

int puntosDentro = 0;

int quiereEntrar[NUM_HILOS] = {0, 0};
int turno = 0;

void entrarSeccionCritica(int id)
{
    int otro = 1 - id;

    quiereEntrar[id] = 1;

    while (quiereEntrar[otro])
    {
        if (turno == otro)
        {
            quiereEntrar[id] = 0;

            while (turno == otro)
            {
                // Espera activa
            }

            quiereEntrar[id] = 1;
        }
    }
}

void salirSeccionCritica(int id)
{
    int otro = 1 - id;

    turno = otro;
    quiereEntrar[id] = 0;
}

void *monteCarlo(void *arg)
{
    int id = *(int *)arg;

    int puntosPorHilo = TOTAL_PUNTOS / NUM_HILOS;

    for (int i = 0; i < puntosPorHilo; i++)
    {
        // Generar x e y entre -1 y 1
        double x = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
        double y = ((double)rand() / RAND_MAX) * 2.0 - 1.0;

        // Verificar si el punto está dentro del círculo
        if (x * x + y * y <= 1.0)
        {
            entrarSeccionCritica(id);

            puntosDentro++;

            salirSeccionCritica(id);
        }
    }

    return NULL;
}

int main(void)
{
    clock_t inicio = clock();

    pthread_t hilo1, hilo2;

    int id1 = 0;
    int id2 = 1;

    srand(time(NULL));

    pthread_create(&hilo1, NULL, monteCarlo, &id1);
    pthread_create(&hilo2, NULL, monteCarlo, &id2);

    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    double pi = 4.0 * puntosDentro / TOTAL_PUNTOS;

    printf("Puntos totales: %d\n", TOTAL_PUNTOS);
    printf("Puntos dentro: %d\n", puntosDentro);
    printf("Aproximacion de Pi: %.6f\n", pi);

    clock_t fin = clock();

    double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;

    printf("Tiempo de CPU: %f segundos\n", tiempo);

    return 0;
}