#include <pthread.h>
#include <stdio.h>

struct thread_data
{
    int num;
    int id;
    int suma;
    int factorial;
};
int i;
void *suma(void *param);
void *factorial(void *param);

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
            pthread_create(&threads[i], &attrs[i], factorial, &t_data[i]);
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

void *suma(void *param)
{
    struct thread_data *my_data;
    my_data = (struct thread_data *)param;

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

void *factorial(void *param)
{
    struct thread_data *my_data;
    my_data = (struct thread_data *)param;

    int i, upper = my_data->num;
    my_data->factorial = 1;

    printf("Thread %d\n", my_data->id);
    if (upper > 0)
    {
        for (i = 1; i <= upper; i++)
        {
            my_data->factorial *= i;
            printf("Thread %d, Factorial %d\n", my_data->id, my_data->factorial);
            usleep(10000);
        }
    }

    pthread_exit(0);
}
