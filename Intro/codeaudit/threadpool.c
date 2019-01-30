#include "threadpool.h"

void* threadpool_thread(void* vargp) {

}

void dispatch(thread_pool* tp, function fn, void* arg) {

}

thread_pool* new_thread_pool(size_t size) {
    thread_pool *new = malloc(sizeof(thread_pool));
    *new = (thread_pool) {
        .threads = (pthread_t*) malloc(sizeof(pthread_t) * size),
        .num_threads = size,
        .q_top = NULL,
        .q_bottom = NULL,
        .lock = PTHREAD_MUTEX_INITIALIZER
    };

    for (size_t i = 0; i < size; i++) {
        if ( pthread_create(&(new->threads[i]), NULL, threadpool_thread, 
                                                    (void*) new) != 0 ) {
            perror("threadpool init failed");
            exit(1);
        }
    }
}

void destroy_thread_pool(thread_pool* tp) {
    while (tp->q_top != NULL) {
        tp_task_t* cur = tp->q_top;
        tp->q_top = tp->q_top->prev;
        free(cur);
    }
}

