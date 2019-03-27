#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#include <unistd.h>
#include <semaphore.h>
#include <sys/mman.h>

#include "custom.h"

char *get_shared_pointer(char *name, size_t size) {
  
  char *pointer;
  int fd;
  
  if ((fd = shm_open(name, O_RDWR | O_CREAT, 0666)) == -1) {
    fprintf(stderr, "error: abriendo objeto de memoria compartida '%s'.\n", name);
    return NULL;
  }
  if (ftruncate(fd, size) != 0) {
    fprintf(stderr, "error: cambiando size de memoria compartida '%s'.\n", name);
    return NULL;
  }
  if ((pointer = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED) {
    fprintf(stderr, "error: mapeando segmento de memoria compartida '%s'.\n", name);
    return NULL;
  }
  close(fd);
  
  return pointer;
  
}

void free_shared_pointer(void *pointer, char *name, size_t size) {
  munmap(pointer, size);
  shm_unlink(name);
  return;
}

sem_t *get_semaphore(char *name) {
  sem_t *semaphore;

  if ((semaphore = sem_open(name, O_CREAT, 0666, 0)) == SEM_FAILED) {
    return NULL;
  }

  return semaphore;
}
/*
void cplfreesemaphore(sem_t *semaphore, char *name) {
  sem_close(semaphore);
  sem_unlink(name);
}
*/
void read_from_shmem(void) {
  sem_wait(sem_dealer2player_written);
  memcpy(command, shm_dealer2player, BUF_SIZE-1);
  sem_post(sem_dealer2player_read);
}


void write_to_shmem(void) {
  memcpy(shm_player2dealer, command, BUF_SIZE-1);
  sem_post(sem_player2dealer_written);
  sem_wait(sem_player2dealer_read);
}
