#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

sem_t first_mutex, second_mutex;
// (r1, s1) = (A, first_mutex)
// (r2, s2) = (B, second_mutex)

void *do_work_one(void *param) {
  pthread_t id_thread;
  id_thread = pthread_self();
  while (1) {
    /* --------------------------- */
    printf("thread_id: %lu solicita recurso: A\n", id_thread);
    sem_wait(&first_mutex);
    printf("thread_id: %lu consegue acesso ao recurso: A\n", id_thread);
    /* --------------------------- */
    printf("thread_id: %lu solicita recurso: B\n", id_thread);
    sem_wait(&second_mutex);
    printf("thread_id: %lu consegue acesso ao recurso: B\n", id_thread);
    /* --------------------------- */
    sem_post(&second_mutex);
    printf("thread_id: %lu libera o recurso: B\n", id_thread);
    /* --------------------------- */
    sem_post(&first_mutex);
    printf("thread_id: %lu libera o recurso: A\n", id_thread);
    /* --------------------------- */
  }
  pthread_exit(0);
}

void *do_work_two(void *param) {
  pthread_t id_thread;
  id_thread = pthread_self();
  while (1) {
    /* --------------------------- */
    printf("thread_id: %lu solicita recurso: B\n", id_thread);
    sem_wait(&second_mutex);
    printf("thread_id: %lu consegue acesso ao B\n", id_thread);
    /* --------------------------- */
    printf("thread_id: %lu solicita recurso: A\n", id_thread);
    sem_wait(&first_mutex);
    printf("thread_id: %lu consegue acesso ao recurso: A\n", id_thread);
    /* --------------------------- */
    sem_post(&first_mutex);
    printf("thread_id: %lu libera o recurso: A\n", id_thread);
    /* --------------------------- */
    sem_post(&second_mutex);
    printf("thread_id: %lu libera o recurso: B\n", id_thread);
    /* --------------------------- */
  }
  pthread_exit(0);
}
int main(void) {
  sem_init(&first_mutex, 0, 1);
  sem_init(&second_mutex, 0, 1);
  pthread_t first_thread, second_thread;
  pthread_create(&first_thread, NULL, do_work_one, NULL);
  pthread_create(&second_thread, NULL, do_work_two, NULL);
  pthread_join(first_thread, NULL);
  pthread_join(second_thread, NULL);
	return 0;
}
