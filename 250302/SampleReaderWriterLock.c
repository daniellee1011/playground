// #ifndef _READER_WRITER_LOCK_H
// #define _READER_WRITER_LOCK_H

// #include <stdbool.h>
// #include <stdint.h>

// #include <pthread.h>
// #include <semaphore.h>

// typedef struct {
//     uint32_t ReaderCount;
//     sem_t * pWriterSemaphore;
//     pthread_mutex_t ReaderMutex;
// } ReaderWriterLockHandleT;

// typedef void (* OnReadLockedFn)(void * context);
// typedef void (* OnWriteLockedFn)(void * context);

// bool ReaderWriterLockOpen(ReaderWriterLockHandleT ** ppReaderWriterLockHandle);
// bool ReaderWriterLockClose(ReaderWriterLockHandleT * pReaderWriterLockHandle);

// bool ReaderWriterLockDoRead(ReaderWriterLockHandleT * pReaderWriterLockHandle,
//                             OnReadLockedFn pOnReadLockedFn,
//                             void * context);

// bool ReaderWriterLockDoWrite(ReaderWriterLockHandleT * pReaderWriterLockHandle,
//                              OnWriteLockedFn pOnWriteLockedFn,
//                              void * context);

// #endif // _READER_WRITER_LOCK_H

// /* Error-handling reduced for brevity; discuss during interview */
// bool ReaderWriterLockDoRead(ReaderWriterLockHandleT * pReaderWriterLockHandle,
//     OnReadLockedFn pOnReadLockedFn,
//     void * context)
// {
// if (NULL == pReaderWriterLockHandle || NULL == pOnReadLockedFn)
// return false;

// // Acquire the Readers Lock which protects Counting Variable
// (void)pthread_mutex_lock(&(pReaderWriterLockHandle->ReaderMutex));

// pReaderWriterLockHandle->ReaderCount++;

// if (1 == pReaderWriterLockHandle->ReaderCount) // If readers active, acquire Writer Lock
// (void)sem_wait(pReaderWriterLockHandle->pWriterSemaphore);

// (void)pthread_mutex_unlock(&(pReaderWriterLockHandle->ReaderMutex)); // Allow more Readers

// // ****** N Readers & Write Protected ******
// pOnReadLockedFn(context);
// // ****************************************

// // Reduce Reader Counter and Potentially Unlock Writer's Mutex (reverse of above)
// (void)pthread_mutex_lock(&(pReaderWriterLockHandle->ReaderMutex));

// pReaderWriterLockHandle->ReaderCount--;

// if (0 == pReaderWriterLockHandle->ReaderCount)
// (void)sem_post(pReaderWriterLockHandle->pWriterSemaphore);

// (void)pthread_mutex_unlock(&(pReaderWriterLockHandle->ReaderMutex));

// return true;
// }

// /* Error-handling reduced for brevity; discuss during interview */
// bool ReaderWriterLockDoWrite(ReaderWriterLockHandleT * pReaderWriterLockHandle,
//     OnWriteLockedFn pOnWriteLockedFn,
//     void * context)
// {
// if (NULL == pReaderWriterLockHandle || NULL == pOnWriteLockedFn)
// return false;

// (void)sem_wait(pReaderWriterLockHandle->pWriterSemaphore);

// // ****** 0 Readers & Write Protected ******
// // If you spot errors in our code, please make sure to
// // interview with Axon Platform Firmware Team! ;-)
// pOnWriteLockedFn(context);
// // ****************************************

// (void)sem_post(pReaderWriterLockHandle->pWriterSemaphore);

// return true;
// }
