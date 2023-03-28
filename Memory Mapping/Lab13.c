
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include<sys/mman.h>
#include<fcntl.h>
#include<unistd.h>
#include<semaphore.h>
#include <pthread.h>

int count = 0; // shared variable 
sem_t count_sem; // semaphore to synchronize acces to the count variable

	// thread 1
	void * thread1_func(void *arg) {
		int len = strlen(argv[2]);
		for (int i = 0; i < size/2; i++) {
			if (strncmp(&data[i], argv[2], len) == 0) {
				// wait for access to count
				sem_wait(&count_sem);
				count++;
				// release access to count
				sem_post(&count_sem);
			}
		}
		pthread_exit(NULL);
	}

	// thread 2
	void * thread2_func(void *arg) {
		int len = strlen(argv[2]);
		for (int i = size/2; i < size; i++) {
			if (strncmp(&data[i], argv[2], len) == 0) {
				// wait for access to count
				sem_wait(&count_sem);
				count++;
				// release access to count
				sem_post(&count_sem);
			}
		}
		pthread_exit(NULL);
	}


int main (int argc, char *argv[]) {
	

	if (argc != 3) {
		fprintf(stderr, "Usage: %s <filename> <substring>\n", argv[0]);
		exit(1);
	}

	// open file
	FILE *fp;fp = fopen(argv[1], "r");
	if (fp == NULL)
	 {
		fprintf(stderr, "Error opening file\n");
		exit(1);
	}

	// get file size
	fseek(fp, 0, SEEK_END);
	long int size = ftell(fp);
	rewind(fp);

	// create memory map
	char *data;
	data = mmap(NULL, size, PROT_READ, MAP_SHARED, fileno(fp), 0);
	if (data == MAP_FAILED) {
		fprintf(stderr, "Error mapping memory\n");
		exit(1);
	}

	// create threads
	pthread_t thread1, thread2;
	
	// initialize semaphore
	sem_init(&count_sem, 0, 1);

	// create threads
	pthread_create(&thread1, NULL, thread1_func, NULL);
	pthread_create(&thread2, NULL, thread2_func, NULL);

	// wait for threads to finish
	pthread_join (thread1, NULL);
	pthread_join (thread2, NULL);

	// print count
	printf("%d\n", count);

	// delete semaphore
	sem_destroy(&count_sem);

	// close file
	fclose(fp);

	return 0;
}
