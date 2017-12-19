#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int
main()
{
    int c;
    int shmid;
    key_t key = 02577;
    int * addr;

    shmid = shmget(key, 4096, IPC_CREAT | 0666);
    printf("Created shared memory at %d\n", shmid);
    addr = (int *) shmat(shmid, NULL, 0);
    printf("Enter the counter value\n");
    scanf("%d", &c);
    *addr = c;
    while (1) ;
    return 0;
}
