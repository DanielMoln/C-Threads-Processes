#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

int x = 2;

// Threads sharing memory

void * routine()
{
    x++;
    sleep(2);
    printf("Thread1: Value of x = %d \n", x);
}

void * routine2()
{
    sleep(2);
    printf("Thread2: Value of x = %d \n", x);
}

int mails = 0;
pthread_mutex_t mutex;

void * testRaceConditions()
{
    for (size_t i = 0; i < 1000000; i++)
    {
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
    }
}

void * roll_dice()
{
    int value = (rand() % 6) + 1;
    int * result = malloc(sizeof(int));
    *result = value;
    return (void *) result;
}

int primes[10] = { 2, 3, 5, 7, 11, 13, 15, 17, 19, 23 }; 

/*
    (pthread_create(th + i, NULL, &passFunction, NULL)
                                                - HERE -
    The last parameter of pthread_create will pass an argument to the passFunction
    which holds the memory address where we are now.

    In this case just the the pointer of the current index
*/
void * passFunction(void * arg)
{
    sleep(1);
    int index = * ((int *) arg);
    printf("%d\n", primes[index]);
    free(arg);
}

void sumOfAnArray()
{
   pthread_t th[2];

   int i;
   for (i = 0; i < 2; i++)
   {
        int* a = malloc(sizeof(int));
        *a = i;

        if (pthread_create(th + i, NULL, &passFunction, &i) != 0)
        {
            printf("Failed to create the %dth thread.", (i + 1));   
        }
   }

   for (i = 0; i < 2; i++)
   {
        if (pthread_join(th[i], NULL) != 0)
        {
            printf("Failed to join the %dth thread.", (i + 1));   
        }
   }
}

void passUniqueValueToThread()
{
    /*
    
        Problem:
            Create 10 threads, each taking
            a unique prime from the primes
            array and print it on the screen

    */

    /*
    
        Common problem:

        pthread_t th[10];

        int i;
        for (i = 0; i < 10; i++)
        {
                if (pthread_create(th + i, NULL, &passFunction, &i) != 0)
                {
                    printf("Failed to create the %dth thread.", (i + 1));   
                }
        }

        for (i = 0; i < 10; i++)
        {
                if (pthread_join(th[i], NULL) != 0)
                {
                    printf("Failed to join the %dth thread.", (i + 1));   
                }
        }

        I pass the i by reference and in the for loop if the thread created slowly then
        the I's value is going to change and because of that the function will use the newly
        created value of i.
    
    */
   pthread_t th[10];

   int i;
   for (i = 0; i < 10; i++)
   {
        int* a = malloc(sizeof(int));
        *a = i;
        if (pthread_create(th + i, NULL, &passFunction, &i) != 0)
        {
            printf("Failed to create the %dth thread.", (i + 1));   
        }
   }

   for (i = 0; i < 10; i++)
   {
        if (pthread_join(th[i], NULL) != 0)
        {
            printf("Failed to join the %dth thread.", (i + 1));   
        }
   }
}

void getValueFromThread()
{
    int* res;
    srand(time(NULL));

    pthread_t t1;
    if (pthread_create(&t1, NULL, &roll_dice, NULL) != 0)
    {
        printf("Failed to create the thread :(\n");
        return;
    }

    if (pthread_join(t1, &res) != 0)
    {
        printf("Failed to wait the thread :(\n");
        return;
    }

    printf("Result: %d\n", *res);
    free(res);
}

void threads()
{
    pthread_t threads[4];

    // Initialize mutex before using it (NULL = set everything to default)
    pthread_mutex_init(&mutex, NULL);
    int i;
    for (i = 0; i < 4; i++)
    {
        if (pthread_create(threads + i, NULL, &testRaceConditions, NULL) != 0)
        {
            printf("Failed to create thread #1!\n");
        }

        printf("Thread %d started\n", (i + 1));
    }

    for (i = 0; i < 4; i++)
    {
        if (pthread_join(threads[i], NULL) != 0)
        {
            printf("Failed to join the created thread!\n");
        }

        printf("Thread %d has finished execution\n", (i + 1));
    }

    pthread_mutex_destroy(&mutex);
    printf("Number of mails: %d\n", mails);
}

void * exampleFunctionForTryLock(void * arg)
{
    pthread_mutex_lock(&mutex);

    printf("Got lock\n");
    sleep(1);

    pthread_mutex_unlock(&mutex);
}

void tryLockExample()
{
    pthread_t th[4];
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < 4; i++)
    {
        if (pthread_create(&th[i], NULL, &exampleFunctionForTryLock, NULL) != 0)
        {
            printf("Failed to create threads!");
        }
    }

    for (int i = 0; i < 4; i++)
    {
        if (pthread_join(th[i], NULL) != 0)
        {
            printf("Failed to create threads!");
        }
    }

    pthread_mutex_destroy(&mutex);
}