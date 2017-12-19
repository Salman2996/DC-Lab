// gcc -std=c++11 -pthread DistExclusion.cpp

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define work_size 1024
void *thread_func(void *arg);
pthread_mutex_t work_mutex;
char work_area[work_size];
int time_to_exit = 0;

int main() {
  int res;
  pthread_t a_thread;
  void *thread_result;
  res = pthread_mutex_init(&work_mutex, NULL);
  res = pthread_create(&a_thread, NULL, thread_func, NULL);
  if (res != 0) {
    perror("thread creation failure");
    exit(0);
  }
  pthread_mutex_lock(&work_mutex);
  printf("input some text,end to finish \n");
  while (!time_to_exit) {
    fgets(work_area, work_size, stdin);
    pthread_mutex_unlock(&work_mutex);
    while (1) {
      pthread_mutex_lock(&work_mutex);
      if (work_area[0] != '\0') {
        pthread_mutex_unlock(&work_mutex);
        sleep(1);
      } else {
        break;
      }
    }
  }
  pthread_mutex_unlock(&work_mutex);
  printf("\n waiting for thread to finish...");
  res = pthread_join(a_thread, &thread_result);
  printf("thread joined");
  pthread_mutex_destroy(&work_mutex);
  exit(0);
}
void *thread_func(void *arg) {
  sleep(1);
  pthread_mutex_lock(&work_mutex);
  while (strcmp("end\n", work_area)) {
    printf("you input %ld char :%s \n", strlen(work_area) - 1, work_area);
    work_area[0] = '\0';
    pthread_mutex_unlock(&work_mutex);
    sleep(1);
    pthread_mutex_lock(&work_mutex);
  }
  time_to_exit = 1;
  pthread_mutex_unlock(&work_mutex);
  exit(0);
}
