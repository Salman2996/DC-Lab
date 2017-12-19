//gcc -pthread SharedCounter.c
//./a.out sharedMem.txt 10

#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include <sys/mman.h>


sem_t mutex; /* the mutex: a Posix memory-based semaphore */
int *count; /* and the counter */

int main(int argc, char **argv)
{
    int fd, i, nloop;
    struct shared *ptr;
    nloop = atoi(argv[2]);

    /* open file, initialize to 0, map into memory */
    fd = open(argv[1], O_RDWR | O_CREAT, 0666);
    write(fd, &count, sizeof(count));
    count = mmap(NULL, sizeof(count), PROT_READ | PROT_WRITE,MAP_SHARED, fd, 0);
    close(fd);
    
    /* initialize semaphore that is shared between processes */
    sem_init(&mutex, 0, 1);
    
    //setbuf(stdout, NULL); /* stdout is unbuffered */
    if (fork() == 0) { /* child */
        for (i = 0; i < nloop; i++) {
            sem_wait(&mutex);
            printf("child: %d\n",  (*count)++);
            sem_post(&mutex);
        }
        exit(0);
    }
    
    /* parent */
    for (i = 0; i < nloop; i++) {
        sem_wait(&mutex);
        printf("parent: %d\n", (*count)++);
        sem_post(&mutex);
    }
    exit(0);
}