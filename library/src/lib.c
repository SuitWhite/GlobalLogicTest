#include "lib.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 
sem_t sem;
int thread_count = 0;
int found = 0; 

int is_dir(char *path) {
    DIR *dir = opendir(path);
    if (dir) {
        closedir(dir);
        return 1;
    }
    return 0;
}

char *concat_path(char *s1, char *s2) {
    char *result = malloc(strlen(s1) + strlen(s2) + 2);
    strcpy(result, s1);
    if (result[strlen(result)-1] != '/')
        strcat(result, "/");
    strcat(result, s2);
    return result;
}

bool search_file(char* name, char* path){
    DIR *dir = opendir(path); 
    if (dir == NULL) {
        perror("opendir");
        return false;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL && !found) {
        char *entry_name = entry->d_name; 
        if (strcmp(entry_name, ".") == 0 || strcmp(entry_name, "..") == 0) {
            continue; 
        }
        char *entry_path = concat_path(path, entry_name); 
        if (strcmp(entry_name, name) == 0) { 
            pthread_mutex_lock(&mutex); 
            if (!found) { 
                printf("File found at %s\n", entry_path); 
                found = 1; 
            }
            pthread_mutex_unlock(&mutex); 
        } else if (is_dir(entry_path)) { 
            search_file(name, entry_path);
        }
        free(entry_path); 
    }

    closedir(dir); 

    return false;
}

void* thread_func(void *arg){
    thread_arg *targ = (thread_arg *) arg; 
    char *name = targ->name; 
    char *path = targ->path; 
    free(targ); 

    search_file(name, path);

    sem_post(&sem);

    free(path);

    pthread_exit(NULL);
}

void search_file_with_threads(char *name, char* path) {
    DIR *dir = opendir(path); 
    if (dir == NULL) {
        perror("opendir");
        exit(-1);
    }
    
    sem_init(&sem, 0, MAX_THREADS);

    struct dirent *entry; 
    pthread_t *threads = malloc(sizeof(pthread_t)*MAX_DIRS);
    int number_of_threads = 0;
    while ((entry = readdir(dir)) != NULL && !found) {
        char *entry_name = entry->d_name;
        if (strcmp(entry_name, ".") == 0 || strcmp(entry_name, "..") == 0) {
            continue; 
        }
        char *entry_path = concat_path(path, entry_name);
        if (is_dir(entry_path)){
            sem_wait(&sem);

            number_of_threads++;

            thread_arg *new_arg = malloc(sizeof(thread_arg));
            new_arg->name = name; 
            new_arg->path = entry_path; 
            pthread_create(&threads[number_of_threads], NULL, thread_func, new_arg);
        }
    }

    for (int i = 0; i < number_of_threads; i++) {
        pthread_join(threads[i], NULL);
        fflush(stdout);
    }
    free(threads);
    sem_destroy(&sem);
}
