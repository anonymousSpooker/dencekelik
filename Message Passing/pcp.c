#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex, full, empty;
int buffer[5], put=0, get=0, item=1, producerThreads[20], consumerThreads[20], gitem;

void *producer(void *arg){
    do{
        sem_wait(&empty);
        sem_wait(&mutex);
        buffer[put%5] = item;

        int *myId = (int *)arg;
        printf("\nPRODUCER %d PRODUCES %d ITEM => BUFFER[%d] : %d\n", *myId, buffer[put%5], put%5, item);

        item++;
        put++;

        sem_post(&mutex);
        sem_post(&full);
    } while (1);
}

void *consumer(void *arg){
    do{
        sem_wait(&full);
        sem_wait(&mutex);
        gitem = buffer[get%5];

        int *myId = (int *)arg;
        printf("\nCONSUMER %d CONSUMES %d ITEM OF BUFFER[%d]", *myId, gitem, get%5);

        get++;

        sem_post(&mutex);
        sem_post(&empty);
    } while (1);
}

int main(){
    
    int producers, consumers;
    printf("Enter the number of Producers: ");
    scanf("%d", &producers);
    printf("Enter the number of Consumers: ");
    scanf("%d", &consumers);

    sem_init(&mutex,0,1);
    sem_init(&full,0,0);
    sem_init(&empty,0,5);

    pthread_t a[10],b[10];
    for(int i=0; i<producers; i++){
        producerThreads[i] = i+1;
        pthread_create(&a[i], NULL, producer, (void *)&producerThreads[i]);
    }
    for(int i=0; i<consumers; i++){
        consumerThreads[i] =  i+1;
        pthread_create(&b[i], NULL, consumer, (void *)&consumerThreads[i]);
    }
    for(int i=0; i<producers; i++){
        pthread_join(a[i], NULL);
    }
    for(int i=0; i<consumers; i++){
        pthread_join(b[i], NULL);
    }

    return 0;
}