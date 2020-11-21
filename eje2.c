
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
    pthread_attr_t attr[NUM_THREADS];

    sem_init(&sem[0], 0, 1);
    sem_init(&sem[1], 0, 0);
    sem_init(&sem[2], 0, 0);

    int i;
    for (i = 0; i < NUM_THREADS; i++)
    {
        pthread_attr_init(&attr[i]);
        tData[i].id = i;
        pthread_create(&tList[i], &attr[i], runner, &tData[i]);
    }

    for (i = 0; i < NUM_THREADS; i++)
        pthread_join(tList[i], NULL);
    for (i = 0; i < NUM_THREADS; i++)
        sem_destroy(&sem[i]);
    printf("------ Press Any key to continue ------\n");

    return 0;
}

void *runner(void *in)
{
    int i;
    struct thread_data *dat;
    dat = (struct thread_data *)in;

    sem_wait(&sem[dat->id]);

    printf("Proceso:%d en ejecución\n", dat->id);
    usleep(6000);
    printf("Proceso:%d en seccion restante\n", dat->id);

    if (dat->id == 0)
    {
        sem_post(&sem[2]);
    }
    else
    {
        sem_post(&sem[1]);
    }

    pthread_exit(0);
}
