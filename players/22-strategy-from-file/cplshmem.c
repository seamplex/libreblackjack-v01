/*
 * Extension de RELAP para acople con codigos externos
 *
 *   Septiembre 2011
 *   German Theler - gtheler@tecna.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifndef WINDOWS
  #include <unistd.h>
  #include <semaphore.h>
  #include <sys/mman.h>
#else
  #include <windows.h>
  #define umask  _umask
  #define getpid _getpid
  #define stat   _stat
  #define unlink _unlink
#endif

#include "cpl.h"


void *cplgetsharedpointer(char *name, size_t size, int locked) {

  void *pointer;
  int dangling_pid;
  
#ifndef WINDOWS
  int fd;
#else
  HANDLE fd;
#endif

  if (locked) {
    if ((dangling_pid = cplcreatelock(name, 0)) != 0) {
      printf("%s: error: el segmento '%s' esta siendo usado por el proceso '%d'.\n", CODE_NAME, name, dangling_pid);
      /* si salimos con return NULL eventualmente llega al free() que borra los locks */
      exit(-1);
    }
  }

#ifndef WINDOWS
  umask(0);
  if ((fd = shm_open(name, O_RDWR | O_CREAT, SHARE_MODE)) == -1) {
    printf("%s: error: abriendo objeto de memoria compartida '%s'.\n", CODE_NAME, name);
    return NULL;
  }
  if (ftruncate(fd, size) != 0) {
    printf("%s: error: cambiando size de memoria compartida '%s'.\n", CODE_NAME, name);
    return NULL;
  }
  if ((pointer = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED) {
    printf("%s: error: mapeando segmento de memoria compartida '%s'.\n", CODE_NAME, name);
    return NULL;
  }

  close(fd);
#else
  if ((fd = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, SHARE_FLAGS, 0, size, name)) == NULL) {
    printf("%s: error: creando filemapping de segmento '%s'.\n", CODE_NAME, name);
    return NULL;
  }
  if ((pointer = MapViewOfFile(fd, SHARE_MODE, 0, 0, size)) == NULL) {
    printf("%s: error: haciendo mapa de objeto '%s'.\n", CODE_NAME, name);
    return NULL;
  }
#endif
  return pointer;

}

void cplfreesharedpointer(void *pointer, char *name, size_t size) {
#ifndef WINDOWS
  munmap(pointer, size);
  shm_unlink(name);
#else
  UnmapViewOfFile(pointer);
#endif
}


#ifndef WINDOWS
sem_t *cplgetsemaphore(char *name, int locked) {
  sem_t *semaphore;
  int dangling_pid;

  if (locked) {
    if ((dangling_pid = cplcreatelock(name, 1)) != 0) {
      printf("%s: error: el semaforo '%s' esta siendo usado por el proceso '%d'.\n", CODE_NAME, name, dangling_pid);
      /* si salimos con return NULL eventualmente llega al free() que borra los locks */
      exit(-1);
    }
  }

  umask(0);
  if ((semaphore = sem_open(name, O_CREAT, SHARE_MODE, 0)) == SEM_FAILED) {
    return NULL;
  }

  return semaphore;
}
#else
HANDLE cplgetsemaphore(char *name, int locked) {
  HANDLE semaphore;
  int dangling_pid;

  if (locked) {
    if ((dangling_pid = cplcreatelock(name, 1)) != 0) {
      printf("%s: error: el semaforo '%s' esta siendo usado por el proceso '%d'.\n", CODE_NAME, name, dangling_pid);
      /* si salimos con return NULL eventualmente llega al free() que borra los locks */
      exit(-1);
    }
  }
  if ((semaphore = CreateSemaphore(NULL, 0, 1000, name)) == NULL) {
    return NULL;
  }
  return semaphore;
}
#endif

#ifndef WINDOWS
void cplfreesemaphore(sem_t *semaphore, char *name) {
  sem_close(semaphore);
  sem_unlink(name);
}
#else
void cplfreesemaphore(HANDLE semaphore, char *name) {
  CloseHandle(semaphore);
}
#endif

int cplcreatelock(char *name, int sem) {
  int dangling_pid;
  struct stat dummy;
  FILE *lock_file;
  char *lock_file_name;

  if (stat(relap_cpl.lock_dir, &dummy) == -1) {
    umask(0);
#ifndef WINDOWS
    if (mkdir(relap_cpl.lock_dir, 0777) == -1) {
#else
    _mkdir("C:/TMP");
    if (_mkdir(relap_cpl.lock_dir) == -1) {
#endif
      printf("%s: error: creando directorio de lock '%s'.\n", CODE_NAME, relap_cpl.lock_dir);
      exit(-1);
    }
  }

  lock_file_name = malloc(128);
  sprintf(lock_file_name, "%s/%s%s.lock", relap_cpl.lock_dir, (sem)?("sem."):(""), (name[0]=='/')?(name+1):(name));
  umask(0022);

  if (stat(lock_file_name, &dummy) == -1) {
    if ((lock_file = fopen(lock_file_name, "w")) == NULL) {
      printf("%s: error: abriendo archivo de lock '%s' para escritura.\n", CODE_NAME, lock_file_name);
      exit(-1);
    }
    fprintf(lock_file, "%10d", getpid());
    fclose(lock_file);
  } else {
    if ((lock_file = fopen(lock_file_name, "r")) == NULL) {
      printf("%s: error: abriendo archivo de lock '%s' para lectura.\n", CODE_NAME, lock_file_name);
      exit(-1);
    }
    fscanf(lock_file, "%d", &dangling_pid);
    fclose(lock_file);

#ifndef WINDOWS
    if (kill(dangling_pid, 0) == -1) {
#else
    // en wine, por alguna razon getpid no devuelve el pid real de linux sino
    // un numero entre 1 y 100, asi que en este caso siempre borramos todo al
    // carajo y listo, porque sino el usuario se acostumbra a borrar a mano
    // los locks y eso no es bueno
    if (dangling_pid < 100 || OpenProcess(PROCESS_QUERY_INFORMATION, 0, dangling_pid) == NULL) {
#endif
      printf("%s: warning: borrando stale lock file '%s' dejado por proceso %d.\n", CODE_NAME, lock_file_name, dangling_pid);
      unlink(lock_file_name);
      
      if (cplcreatelock(name,  sem) != 0) {
        return dangling_pid;
      }
    } else {
      return dangling_pid;
    }
  }

  free(lock_file_name);

  return 0;

}

void cplremovelock(char *name, int sem) {
  struct stat dummy;

  char *lock_file_name;

  lock_file_name = malloc(128);
  sprintf(lock_file_name, "%s/%s%s.lock", relap_cpl.lock_dir, (sem)?("sem."):(""), (name[0]=='/')?(name+1):(name));

  if (stat(lock_file_name, &dummy) == -1) {
    printf("%s: advertencia: el archivo de lock '%s' fue borrado externamente.\n", CODE_NAME, lock_file_name);
  } else {
    unlink(lock_file_name);
  }

  free(lock_file_name);

  return;
}

void cplfree_(void) {

   int i;

/* liberamos las cadenas fijas */
   if (relap_cpl.input_file_name != NULL) {
#ifndef WINDOWS
     shm_unlink(relap_cpl.input_file_name);
#endif

     free(relap_cpl.input_file_name);
   }
   if (relap_cpl.output_file_name != NULL) {
#ifndef WINDOWS
     shm_unlink(relap_cpl.output_file_name);
#endif
     free(relap_cpl.output_file_name);
   }
   if (relap_cpl.restart_file_name != NULL) {
#ifndef WINDOWS
     shm_unlink(relap_cpl.restart_file_name);
#endif
     free(relap_cpl.restart_file_name);
   }
   if (relap_cpl.coupling_file_name != NULL) {
#ifndef WINDOWS
     shm_unlink(relap_cpl.coupling_file_name);
#endif
     free(relap_cpl.coupling_file_name);
   }
   if (relap_cpl.problem_title_name != NULL) {
#ifndef WINDOWS
     shm_unlink(relap_cpl.problem_title_name);
#endif
     free(relap_cpl.problem_title_name);
   }
   if (relap_cpl.external_md5sum_name != NULL) {
#ifndef WINDOWS
     shm_unlink(relap_cpl.external_md5sum);
#endif
     free(relap_cpl.external_md5sum_name);
   }



   /* los exports */
   for (i = 0; i < relap_cpl.n_shares; i++) {
     if (relap_cpl.share[i].sem_ready != NULL) {
       cplfreesemaphore(relap_cpl.share[i].sem_ready, relap_cpl.share[i].sem_ready_name);
       if (relap_cpl.share[i].locked) {
         cplremovelock(relap_cpl.share[i].sem_ready_name, 1);
       }
       free(relap_cpl.share[i].sem_ready_name);
     }
     if (relap_cpl.share[i].sem_wait != NULL) {
       cplfreesemaphore(relap_cpl.share[i].sem_wait, relap_cpl.share[i].sem_wait_name);
       if (relap_cpl.share[i].locked) {
         cplremovelock(relap_cpl.share[i].sem_wait_name, 1);
       }
       free(relap_cpl.share[i].sem_wait_name);
     }


     if (relap_cpl.share[i].data != NULL) {
       cplfreesharedpointer(relap_cpl.share[i].data, relap_cpl.share[i].name, sizeof(double)*relap_cpl.share[i].size);
       if (relap_cpl.share[i].locked) {
         cplremovelock(relap_cpl.share[i].name, 0);
       }
       free(relap_cpl.share[i].name);
     }

     if (relap_cpl.share[i].admin != NULL) {
       free(relap_cpl.share[i].admin);
     }
   }


   /* el vector de time status */
   if (relap_cpl.status != NULL) {
     cplfreesharedpointer(relap_cpl.status, relap_cpl.status_name, sizeof(status_t));
     cplremovelock(relap_cpl.status_name, 0);
     free(relap_cpl.status_name);
   }

   /* la cadena del lock dir */
   if (relap_cpl.lock_dir != NULL) {
     free(relap_cpl.lock_dir);
   }


   return;
}



int cplwritestaticdata(char *name, char *data, size_t size) {
  char *shared_pointer;

  if ((shared_pointer = cplgetsharedpointer(name, size, 0)) == NULL)
    return -1;
  memcpy(shared_pointer, data, size);

  return 0;

}

void cplposixname(char *dest, char *source) {

#ifndef WINDOWS
  if (source[0] != '/') {
    sprintf(dest, "/%s", source);
  } else {
    sprintf(dest, "%s", source);
  }
#else
  sprintf(dest, "%s", source);
#endif
  return;
}
