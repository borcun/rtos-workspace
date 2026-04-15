#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int resource = 0;
int ready = 0;

void *consume(void *arg) {
  int id = *((int *) arg);

  pthread_mutex_lock(&lock);

  while (ready == 0) {
    printf("consumer %d: Waiting for resource...\n", id);
    pthread_cond_wait(&cond, &lock);
    printf("consumer %d: Waited for resource...\n", id);
  }
  
  printf("consumer %d used resource %d\n", id, resource);
  ++resource;
  
  pthread_mutex_unlock(&lock);
    
  return NULL;
}

void *produce(void *arg) {
  pthread_mutex_lock(&lock);
  
  resource = 99;
  ready = 1;
  
  puts("producer: resource ready, signaling all...");
  
  pthread_cond_broadcast(&cond);
  pthread_mutex_unlock(&lock);
  
  return NULL;
}

int main() {
  pthread_t producer;
  pthread_t consumers[3];
  int id_list[3] = {1, 2, 3};
    
  pthread_create(&consumers[0], NULL, consume, &id_list[0]);
  pthread_create(&consumers[1], NULL, consume, &id_list[1]);
  pthread_create(&consumers[2], NULL, consume, &id_list[2]);
  pthread_create(&producer, NULL, produce, NULL);

  pthread_join(producer, NULL);
  pthread_join(consumers[0], NULL);
  pthread_join(consumers[1], NULL);
  pthread_join(consumers[2], NULL);

  pthread_cond_destroy(&cond);

  puts("done!");

  return 0;
}
