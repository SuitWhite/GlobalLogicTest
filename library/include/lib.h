#ifndef LIB_H
#define LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_THREADS 8
#define MAX_DIRS 512
#define ROOT_DIR "/"

typedef struct {
    char *name; 
    char *path; 
} thread_arg;

int is_dir(char *path);

char *concat_path(char *s1, char *s2);

bool search_file(char* name, char* path);

void* thread_func(void *arg);

void search_file_with_threads(char *name, char* path);


#endif