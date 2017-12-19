#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int
main()
{
    int shmid, c;
    int ch    = 1;
    key_t key = 02577;
    int * addr;

    shmid = shmget(key, 4096, IPC_CREAT | 0666);
    printf("Accessing shared memory at %d\n", shmid);
    addr = (int *) shmat(shmid, NULL, 0);
    printf("got %d\n", *addr);
    do {
        printf("Enter 1 if you want to increment ");
        scanf("%d", &ch);
        c     = *addr;
        *addr = ++c;
        printf("Counter incremented to %d\n", c);
    } while (ch == 1);
    return 0;
}
