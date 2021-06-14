/***
Avanish Kumar Singh
2017MT10728
References:
1. Operating Systems: Three Easy Pieces, Section 31.5, Reader-Writer Locks
2. https://en.wikipedia.org/wiki/Readers%E2%80%93writer_lock, Wikipedia
3. https://eli.thegreenplace.net/2019/implementing-reader-writer-locks/#id6, Implementing reader-writer locks
***/
#include "rwlock.h"

void InitalizeReadWriteLock(struct read_write_lock * rw)
{
    rw->b = 0;
    sem_init(&rw->r, 0, 1);
    sem_init(&rw->g, 0, 1);
    rw->is_writer_waiting = 0;
    int rc1 = pthread_mutex_init(&rw->lock, NULL);
    if(rc1 != 0)
    {
        printf("Lock initialization failed\n");
        exit(EXIT_FAILURE);
    }
    int rc2 = pthread_cond_init(&rw->cond, NULL);
    if(rc2 != 0)
    {
        printf("Condition variable initialization failed\n");
        exit(EXIT_FAILURE);
    }
}

void ReaderLock(struct read_write_lock * rw)
{
    pthread_mutex_lock(&rw->lock);
    while(rw->is_writer_waiting != 0)
    {
        pthread_cond_wait(&rw->cond, &rw->lock);
    }
    rw->b = rw->b + 1;
    pthread_mutex_unlock(&rw->lock);
}

void ReaderUnlock(struct read_write_lock * rw)
{
    pthread_mutex_lock(&rw->lock);
    rw->b = rw->b - 1;
    if(rw->b == 0)
    {
        pthread_cond_broadcast(&rw->cond);
    }
    pthread_mutex_unlock(&rw->lock);
}

void WriterLock(struct read_write_lock * rw)
{
    pthread_mutex_lock(&rw->lock);
    while(rw->is_writer_waiting != 0)
    {
        pthread_cond_wait(&rw->cond, &rw->lock);
    }
    rw->is_writer_waiting = 1;
    if(rw->b != 0)
    {
        pthread_cond_wait(&rw->cond, &rw->lock);
    }
    pthread_mutex_unlock(&rw->lock);
}

void WriterUnlock(struct read_write_lock * rw)
{
    pthread_mutex_lock(&rw->lock);
    rw->is_writer_waiting = 0;
    pthread_cond_broadcast(&rw->cond);
    pthread_mutex_unlock(&rw->lock);
}
