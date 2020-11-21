
#define NUM_THREADS 3
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>

struct thread_data
{

    int id;
    int time;
    int timeup;
};

void *runner(void *param);

sem_t sem[NUM_THREADS];
int orden[NUM_THREADS];
int main(int argc, char *argv[])
{

    pthread_t tList[NUM_THREADS];
    struct thread_data tData[NUM_THREADS];

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    sem_init(&sem[0], 0, 1);
    sem_init(&sem[1], 0, 1);
    sem_init(&sem[2], 0, 1);

    tData[0].timeup = 0;
    tData[1].timeup = 2;
    tData[2].timeup = 1;

    int i;
    for (i = 0; i < NUM_THREADS; i++)
    {
        tData[i].id = i;
        pthread_create(&tList[i], &attr, runner, &tData[i]);
    }

    for (i = 0; i < NUM_THREADS; i++)
        pthread_join(tList[i], NULL);
    pthread_attr_destroy(&attr);
    pthread_exit(NULL);

    for (i = 0; i < NUM_THREADS; i++)
        sem_destroy(&sem[i]);

    return 0;
}

void *runner(void *param)
{
    int i;
    struct thread_data *dat;
    dat = (struct thread_data *)param;

    sem_wait(&sem[dat->id]);

    printf("Proceso:%d en ejecución\n", dat->id);
    usleep(6000);
    printf("Proceso:%d en seccion restante\n", dat->id);

    sem_post(&sem[dat->timeup]);

    pthread_exit(0);
}
