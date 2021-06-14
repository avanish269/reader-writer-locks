/***
Avanish Kumar Singh
2017MT10728
***/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

struct read_write_lock
{
    sem_t r; //Protects b and used only by readers
    int b; //Tracks number of blocking readers
    sem_t g; //Ensures mutual exclusion of writers
    int is_writer_waiting;
    pthread_mutex_t lock;
    pthread_cond_t cond;
};

void InitalizeReadWriteLock(struct read_write_lock * rw);
void ReaderLock(struct read_write_lock * rw);
void ReaderUnlock(struct read_write_lock * rw);
void WriterLock(struct read_write_lock * rw);
void WriterUnlock(struct read_write_lock * rw);
