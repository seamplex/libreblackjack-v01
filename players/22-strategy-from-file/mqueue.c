#include <unistd.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <mqueue.h>

#include "custom.h"

int create_mqueue(const char *name, mqd_t *mq) {

  struct mq_attr attr;
  char *posix_name = malloc(strlen(name)+2);
  snprintf(posix_name, strlen(name)+2, "%s%s", (name[0]=='/')?"":"/", name);

  /* initialize the queue attributes */
  attr.mq_flags = 0;
  attr.mq_maxmsg = 10;
  attr.mq_msgsize = 128;
  attr.mq_curmsgs = 0;
  
  if (((*mq) = mq_open(posix_name, O_RDWR | O_CREAT, 0666, &attr)) == -1) {
    printf("error creating '%s'\n", name);
    perror(NULL);
    exit(1);
  }
  
  free(posix_name);
  
  return 0;
}

void write_to_mqueue(void) {
  if (mq_send(mq_player2dealer, command, strlen(command)+1, 0) == -1) {
    perror("error writing on queue\n");
    exit(1);
  }
}

void read_from_mqueue(void) {
  if (mq_receive(mq_dealer2player, command, BUF_SIZE-1, NULL) == -1) {
    perror("error reading from queue\n");
    exit(1);
  }
}

int destroy_mqueue(const char *name, mqd_t *mq) {

  struct mq_attr attr;
  char *posix_name = malloc(strlen(name)+2);
  snprintf(posix_name, strlen(name)+2, "%s%s", (name[0]=='/')?"":"/", name);

  mq_close(*mq);
  mq_unlink(posix_name);
  free(posix_name);
  
  return 0;
}