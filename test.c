
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

pthread_mutex_t mutex;
pthread_mutex_t mutex1;
pthread_mutex_t mutex2;

typedef struct {
    int i;
    pthread_mutex_t *left;
    pthread_mutex_t *right;
} Struct;

void printArr(int arr[])
{
    for (int i = 0; arr[i]; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void *print(void *structure)
{
    Struct s = *(Struct *)structure;
    usleep(500);
    for (int i = 0; i < 50; i++)
    {
        pthread_mutex_lock(s.left);
        pthread_mutex_lock(s.right);

        printf("Thread = %i\n", s.i);

        pthread_mutex_unlock(s.left);
        pthread_mutex_unlock(s.right);
    }
    printf("end\n");
    return (NULL);
}

//void *print(void *arr)
//{
//    pthread_mutex_lock(&mutex);
//    for (int i = 0; i < 20; i++)
//        ((int *)arr)[i] = i + ((int *)arr)[i];
//    printArr((int *)arr);
//
//    for (int i = 0; i < 20; i++)
//        ((int *)arr)[i] -= i;
//    printArr((int *)arr);
//    pthread_mutex_unlock(&mutex);
//    printf("end\n");
//    return (NULL);
//}

void *print1(void *n)
{
    for (int i = 0; i < 20; i++)
    {
        pthread_mutex_lock(&mutex1);
        pthread_mutex_lock(&mutex2);

        printf("Thread = %i\n", *(int *)n);

        pthread_mutex_unlock(&mutex1);
        pthread_mutex_unlock(&mutex2);
    }
    printf("end\n");
    return (NULL);
}

void *print2(void *n)
{
    for (int i = 0; i < 20; i++)
    {
        pthread_mutex_lock(&mutex2);
        pthread_mutex_lock(&mutex1);

        printf("Thread = %i\n", *(int *)n);

        pthread_mutex_unlock(&mutex2);
        pthread_mutex_unlock(&mutex1);
    }
    printf("end\n");
    return (NULL);
}

void threads()
{
    pthread_t t1, t2;

    pthread_mutex_init(&mutex1, NULL);
    pthread_mutex_init(&mutex2, NULL);

    Struct s1, s2;
    s1.i = 1;
    s1.left = &mutex1;
    s1.right = &mutex2; // лежит в левой руке

    s2.i = 2;
    s2.left = &mutex2;
    s2.right = &mutex1; // лежит в правой руке

    pthread_create(&t1, NULL, print, (void *)&s1);
    pthread_create(&t2, NULL, print, (void *)&s2);

    pthread_join(t1, NULL);
}

int main()
{
    threads();
    write(1, "Threads closed\n", 16);
}


//void threads()
//{
//    int arr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
//
//    pthread_t t1, t2;
//    pthread_mutex_init(&mutex, NULL);
//
//    pthread_create(&t1, NULL, print, (void *)arr);
//    pthread_create(&t2, NULL, print, (void *)arr);
//
//    pthread_join(t1, NULL);
//    pthread_join(t2, NULL);
//    write(1, "Exit\n", 5);
//}