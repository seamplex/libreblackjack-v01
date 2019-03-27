#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>

#include "custom.h"

int split[10][10];
int soft_double[9][10];
int hard_double[19][10];
int soft_hit[9][10];
int hard_hit[19][10];

int ipc;

void read_from_dealer(void) {
  if (ipc == 0) {
    read_from_shmem();
  } else {
    read_from_mqueue();
  }
}

void write_to_dealer(void) {
  if (ipc == 0) {
    write_to_shmem();
  } else {
    write_to_mqueue();
  }
}



int main(void) {
  
  int upcard;
  int first_card;
  int second_card;
  int further_card;
  int other_cards = 0;
  int count;
  int soft;
  int player_cards_index;
  int upcard_index;
  int done = 0;
  int i, j;
  
  FILE *custom;
  
  custom = fopen("split.txt", "r");
  fgets(command, BUF_SIZE-1, custom);
  for (i = 0; i < 10; i++) {
    fscanf(custom, "%s", command);
    for (j = 0; j < 10; j++) {
      fscanf(custom, "%d", &split[i][j]);
    }
  }
  fclose(custom);

  custom = fopen("soft_double.txt", "r");
  fgets(command, BUF_SIZE-1, custom);
  for (i = 0; i < 9; i++) {
    fscanf(custom, "%s", command);
    for (j = 0; j < 10; j++) {
      fscanf(custom, "%d", &soft_double[i][j]);
    }
  }
  fclose(custom);
  
  custom = fopen("hard_double.txt", "r");
  fgets(command, BUF_SIZE-1, custom);
  for (i = 0; i < 19; i++) {
    fscanf(custom, "%s", command);
    for (j = 0; j < 10; j++) {
      fscanf(custom, "%d", &hard_double[i][j]);
    }
  }
  fclose(custom);
  
  custom = fopen("soft_hit.txt", "r");
  fgets(command, BUF_SIZE-1, custom);
  for (i = 0; i < 9; i++) {
    fscanf(custom, "%s", command);
    for (j = 0; j < 10; j++) {
      fscanf(custom, "%d", &soft_hit[i][j]);
    }
  }
  fclose(custom);
  
  custom = fopen("hard_hit.txt", "r");
  fgets(command, BUF_SIZE-1, custom);
  for (i = 0; i < 19; i++) {
    fscanf(custom, "%s", command);
    for (j = 0; j < 10; j++) {
      fscanf(custom, "%d", &hard_hit[i][j]);
    }
  }
  fclose(custom);
  
  ipc = 1;
  
  if (ipc == 0)  {
    shm_dealer2player = get_shared_pointer("file_d2p", BUF_SIZE-1);
    sem_dealer2player_written = get_semaphore("file_d2p_written");
    sem_dealer2player_read = get_semaphore("file_d2p_read");

    shm_player2dealer = get_shared_pointer("file_p2d", BUF_SIZE-1);
    sem_player2dealer_written = get_semaphore("file_p2d_written");
    sem_player2dealer_read = get_semaphore("file_p2d_read");
  } else {
    create_mqueue("file_d2p", &mq_dealer2player);
    create_mqueue("file_p2d", &mq_player2dealer);
  }
    
  while (done == 0) {
    read_from_dealer();
    if (strcmp(command, "bye") == 0) {
      done = 1;
      
    } else if (strcmp(command, "shuffling") == 0) {
      ; // ok
      
    } else if (strcmp(command, "new_hand") == 0) {
      upcard = first_card = second_card = soft = count = other_cards = 0;
      
    } else if (strncmp(command, "card_player_first", 17) == 0) {
      sscanf(command, "card_player_first %d", &first_card);
      
    } else if (strncmp(command, "card_dealer_up", 14) == 0) {
      sscanf(command, "card_dealer_up %d", &upcard);
      
    } else if (strncmp(command, "card_player_second", 18) == 0) {
      sscanf(command, "card_player_second %d", &second_card);
      
    } else if (strncmp(command, "card_player", 11) == 0) {
      sscanf(command, "card_player %d", &further_card);
      other_cards += further_card;

    // playing decisions, in the order explained by norm      
    } else if (strcmp(command, "bet?") == 0) {
      sprintf(command, "%d", 1);
      write_to_dealer();
      
    } else if (strcmp(command, "insurance?") == 0) {
      sprintf(command, "no");
      write_to_dealer();

      
    } else if (strncmp(command, "play?", 5) == 0) {
      
      if (first_card == 0 || second_card == 0) {
        fprintf(stderr, "error\n");
        sprintf(command, "quit");
        write_to_dealer();
        return -1;
      }
      
      // see if play came with the coun
      sscanf(command, "play? %d %d", &count, &upcard);
      if (count == 0) {
        // ask for the count
        sprintf(command, "count");
        write_to_dealer();
      
        read_from_dealer(); // the count
        sscanf(command, "%d", &count);
      }
      
      soft = (count < 0);
      count = (count < 0) ? -count : count;
      player_cards_index = 20 - count;
      upcard_index = upcard-2;
      
      // TODO: surrender
      
      // split
      if (other_cards == 0) {
        if (first_card == second_card) {
          // the first index is different
          if (split[11-first_card][upcard_index]) {
            second_card = 0;
            sprintf(command, "split");
            write_to_dealer();
            continue;
          }
        }

        // soft double
        if (soft != 0) {
          if (soft_double[player_cards_index][upcard_index]) {
            sprintf(command, "double");
            write_to_dealer();
            continue;
          }
        }

        // hard double
        if (hard_double[player_cards_index][upcard_index]) {
          sprintf(command, "double");
          write_to_dealer();
          continue;
        }
      }
      
      // soft hit
      if (soft != 0 && soft_hit[player_cards_index][upcard_index]) {
        sprintf(command, "hit");
        write_to_dealer();
        continue;
      }

      // hard hit
      if (hard_hit[player_cards_index][upcard_index]) {
        sprintf(command, "hit");
        write_to_dealer();
        continue;
      }
      
      sprintf(command, "stand");
      write_to_dealer();
    }
  }

  if (ipc == 0)  {
    ; // TODO: destroy shmem
  } else {
    destroy_mqueue("file_d2p", &mq_dealer2player);
    destroy_mqueue("file_p2d", &mq_player2dealer);
  }
        
  return 0;
  
}
