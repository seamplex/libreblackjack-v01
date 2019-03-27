#include <semaphore.h>
#include <mqueue.h>

#define BUF_SIZE 256

char *shm_dealer2player;
char *shm_player2dealer;
sem_t *sem_dealer2player_read, *sem_dealer2player_written;
sem_t *sem_player2dealer_read, *sem_player2dealer_written;

mqd_t mq_dealer2player;
mqd_t mq_player2dealer;

char command[BUF_SIZE-1];

char *get_shared_pointer(char *name, size_t size);
void free_shared_pointer(void *pointer, char *name, size_t size);
sem_t *get_semaphore(char *name);
void cplfreesemaphore(sem_t *semaphore, char *name);
void read_from_shmem(void);
void write_to_shmem(void);

int create_mqueue(const char *name, mqd_t *mq);
void write_to_mqueue(void);
void read_from_mqueue(void);
int destroy_mqueue(const char *name, mqd_t *mq);
