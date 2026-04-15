#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SEC_TO_MSEC(sec) ((sec) * 1000 * 1000)

int resource = 0;
sem_t bsem;

void *produce(void *arg) {
  int size = *((int *) arg);
  
  for (int i = 0; i < size; ++i) {
    resource = i;
    printf("produced: %d\n", i);
    sem_post(&bsem);
    
    // to see output step by step
    usleep(SEC_TO_MSEC(0.1));
  }

  return NULL;
}

void *consume(void *arg) {
  int size = *((int *) arg);

  for (int i = 0; i < size; ++i) {
    sem_wait(&bsem);
    printf("consumed: %d\n", resource);
  }  

  return NULL;
}

int main(int argc, char **argv) {
  pthread_t consumer, producer;
  int size = 10;
  
  // initialize semaphore with 0, and indicate that it's shared between threads
  sem_init(&bsem, 0, 0);
  
  pthread_create(&consumer, NULL, consume, &size);
  pthread_create(&producer, NULL, produce, &size);

  pthread_join(producer, NULL);
  pthread_join(consumer, NULL);
  
  sem_destroy(&bsem);

  printf("done!\n");
  
  return 0;
}
