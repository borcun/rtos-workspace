#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SEC_TO_MSEC(sec) ((sec) * 1000 * 1000)

pthread_mutex_t mutex;

int resource = 0;

void *produce(void *arg) {
  int size = *((int *) arg);
  
  for (int i = 0; i < size; ++i) {
    // critical section
    pthread_mutex_lock(&mutex);
    resource = i;
    printf("produced: %d\n", resource);
    pthread_mutex_unlock(&mutex);

    // to see output step by step
    usleep(SEC_TO_MSEC(0.1));
  }

  return NULL;
}

void *consume(void *arg) {
  int size = *((int *) arg);

  for (int i = 0; i < size; ++i) {
    // critical section
    pthread_mutex_lock(&mutex);
    printf("consumed: %d\n", resource);
    pthread_mutex_unlock(&mutex);

    // to see output step by step
    usleep(SEC_TO_MSEC(0.1));
  }  

  return NULL;
}

int main(int argc, char **argv) {
  pthread_t consumer, producer;
  int size = 10;

  pthread_mutex_init(&mutex, NULL);
  
  pthread_create(&producer, NULL, produce, &size);
  pthread_create(&consumer, NULL, consume, &size);

  pthread_join(consumer, NULL);
  pthread_join(producer, NULL);
  
  pthread_mutex_destroy(&mutex);

  printf("done!\n");
  
  return 0;
}
