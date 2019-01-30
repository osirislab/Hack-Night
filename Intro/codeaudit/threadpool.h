#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

typedef void (*function)(void*);

typedef struct task {
    function fn;
    void* args;
    struct task* next;
    struct task* prev;
} tp_task_t;

typedef struct thread_pool_s {
    pthread_t* threads;
    size_t num_threads;

    pthread_mutex_t lock;

    tp_task_t* q_top;
    tp_task_t* q_bottom;
} thread_pool;

thread_pool* new_thread_pool(size_t size);
void destroy_thread_pool(thread_pool* tp);

void dispatch(thread_pool* tp, function fn, void* arg);
