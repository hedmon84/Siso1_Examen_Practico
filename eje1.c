#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct thread_data
{
    int num;
    int id;
    int suma;
    int factorial;
};
int i;
void *suma(void *data);
void *fact(void *data);

int main(int argc, char *argv[])
{
    struct thread_data t_data[12];
    pthread_t threads[12];
    pthread_attr_t attrs[12];

    if (argc > 11)
    {
        fprintf(stderr, "Maximo 10 parametros: %d \n", argc);
        return -1;
    }
    for (i = 1; i < argc; i++)
    {
        t_data[i].id = i;
        t_data[i].num = atoi(argv[i]);
        pthread_attr_init(&attrs[i]);

        if (i % 2 != 0)
        {
            pthread_create(&threads[i], &attrs[i], suma, &t_data[i]);
        }
        else
        {
            pthread_create(&threads[i], &attrs[i], fact, &t_data[i]);
        }
    }

    for (i = 1; i < argc; i++)
    {
        pthread_join(threads[i], NULL);
    }

    for (i = 1; i < argc; i++)
    {

        if (i % 2 != 0)
            printf("Thread %d Suma Total %d ...\n", t_data[i].id, t_data[i].suma);
        else
            printf("Thread %d Factorial Total %d ...\n", t_data[i].id, t_data[i].factorial);
    }
}

void *suma(void *data)
{
    struct thread_data *my_data;
    my_data = (struct thread_data *)data;

    int i, upper = my_data->num;
    my_data->suma = 0;

    printf("Thread %d\n", my_data->id);
    if (upper > 0)
    {
        for (i = 1; i <= upper; i++)
        {
            my_data->suma += i;
            printf("Thread %d, Suma Parcial %d\n", my_data->id, my_data->suma);
            usleep(10000);
        }
    }

    pthread_exit(0);
}

void *fact(void *data)
{
    struct thread_data *Mdat;
    Mdat = (struct thread_data *)data;

    int i, upper = Mdat->num;
    Mdat->factorial = 1;

    printf("Thread %d\n", Mdat->id);
    if (upper > 0)
    {
        for (i = 1; i <= upper; i++)
        {
            Mdat->factorial *= i;
            printf("Thread %d, Factorial %d\n", Mdat->id, Mdat->factorial);
            usleep(10000);
        }
    }

    pthread_exit(0);
}
