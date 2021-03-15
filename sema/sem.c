//
//  semaphore_critical_reason.c
//  semaphore_critical_reason
//

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <unistd.h>


void* protect_critical_region(void* n) {
  int i = 0, thread_num = (int)(long)n;
  bool finished = false;

  //Initialization

  sem_t mutex, mutex2, mutex3;
  sem_init(&mutex, 0, 1);
  sem_init(&mutex2, 0, 1);
  sem_init(&mutex3, 0 , 1);

  while (!finished) {
		sem_wait(&mutex);// TODO: FILL IN THIS LINE		
    for (int j = 0; j < thread_num; ++j) { printf("\t\t\t"); }
    printf("CRITICAL(T%d)\n", thread_num);
		sem_post(&mutex);		// TODO: FILL IN THIS LINE

    sleep(2);

		sem_wait(&mutex2);		// TODO: FILL IN THIS LINE
    for (int j = 0; j < thread_num; ++j) { printf("\t\t\t"); }
    printf("out of CRITICAL(T%d)\n", thread_num);
		sem_post(&mutex2);		// TODO: FILL IN THIS LINE
    
    finished = i++ > 3;

		sem_post(&mutex3);		// TODO: FILL IN THIS LINE
    for (int j = 0; j < thread_num; ++j) { printf("\t\t\t"); }
    printf("into non-critical(T%d)\n", thread_num);
		sem_post(&mutex3);		// TODO: FILL IN THIS LINE
  }
  return NULL; 
}


#define N_THREADS 3

int main(int argc, const char* argv[]) {
  pthread_t tid[N_THREADS];
  pthread_attr_t attr;
  
  pthread_attr_init(&attr);
  
  for (int i = 0; i < N_THREADS; ++i) {
    pthread_create(&tid[i], &attr, protect_critical_region, (void*)(long)i);
  }
  
  for (int i = 0; i < N_THREADS; ++i) {
    pthread_join(tid[i], NULL);
  }
  printf("\nall %d threads joined", N_THREADS);
  printf("\n\nEnd of program\n");

  return 0;
}


//========================================================================
// OUTPUT (your output will vary)
//========================================================================
//
// 			CRITICAL(T1)
// CRITICAL(T0)
// 						CRITICAL(T2)
// 			out of CRITICAL(T1)
// 			into non-critical(T1)
// 			CRITICAL(T1)
// 						out of CRITICAL(T2)
// 						into non-critical(T2)
// 						CRITICAL(T2)
// out of CRITICAL(T0)
// into non-critical(T0)
// CRITICAL(T0)
// 			out of CRITICAL(T1)
// 						out of CRITICAL(T2)
// out of CRITICAL(T0)
// into non-critical(T0)
// 						into non-critical(T2)
// 						CRITICAL(T2)
// CRITICAL(T0)
// 			into non-critical(T1)
// 			CRITICAL(T1)
// 						out of CRITICAL(T2)
// 						into non-critical(T2)
// 						CRITICAL(T2)
// out of CRITICAL(T0)
// into non-critical(T0)
// CRITICAL(T0)
// 			out of CRITICAL(T1)
// 			into non-critical(T1)
// 			CRITICAL(T1)
// 						out of CRITICAL(T2)
// out of CRITICAL(T0)
// into non-critical(T0)
// CRITICAL(T0)
// 			out of CRITICAL(T1)
// 			into non-critical(T1)
// 			CRITICAL(T1)
// 						into non-critical(T2)
// 						CRITICAL(T2)
// out of CRITICAL(T0)
// into non-critical(T0)
// 			out of CRITICAL(T1)
// 			into non-critical(T1)
// 						out of CRITICAL(T2)
// 						into non-critical(T2)
//
// all 3 threads joined
//
// End of program
// Program ended with exit code: 0
//
//========================================================================
