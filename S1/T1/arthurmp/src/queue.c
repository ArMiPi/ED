#include<stdio.h>
#include<stdlib.h>

#include"queue.h"

#define MAX_QUEUE_SIZE 50

typedef struct queueItem {
    element elem;
}QUEUEITEM;

typedef struct _queue {
    int size;
    int first;
    int last;
    QUEUEITEM *q;
}QUEUE;

queue newQueue() {
    QUEUE *q = (QUEUE *) malloc(sizeof(QUEUE));
    if(q == NULL) {
        printf("ERROR: Could not allocate memory for empty queue\n");
        exit(EXIT_FAILURE);
    }

    q->first = 0;
    q->size = 0;
    q->last = 0;
    q->q = (QUEUEITEM *) malloc(MAX_QUEUE_SIZE * sizeof(QUEUEITEM));
    if(q->q == NULL) {
        printf("ERROR: Could not allocate memory for queue items \n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < MAX_QUEUE_SIZE; i++) q->q[i].elem = NULL;

    return q;
}

bool isQueueEmpty(queue q) {
    if(q == NULL) return true;

    QUEUE *qP = (QUEUE *) q;

    return qP->size == 0;
}

bool isQueueFull(queue q) {
    if(q == NULL) return true;

    QUEUE *qP = (QUEUE *) q;

    return qP->size == MAX_QUEUE_SIZE;
}

void enqueue(queue q, element elem) {
    if(q == NULL || elem == NULL) return;

    if(isQueueFull(q)) {
        printf("WARNING: Queue is full\n");
        return;
    }

    QUEUE *qP = (QUEUE *) q;

    qP->q[qP->last].elem = elem;
    qP->last++;
    if(qP->last == MAX_QUEUE_SIZE) qP->last = 0;
    qP->size++;
}

element dequeue(queue q) {
    if(q == NULL) return NULL;

    if(isQueueEmpty(q)) {
        printf("WARNING: Queue is empty\n");
        return NULL;
    }

    QUEUE *qP = (QUEUE *) q;

    element elem = qP->q[qP->first].elem;
    qP->q[qP->first].elem = NULL;
    qP->first++;
    if(qP->first == MAX_QUEUE_SIZE) qP->first = 0;
    qP->size--;

    return elem;
}

element peekQueue(queue q) {
    if(q == NULL) return NULL;

    if(isQueueEmpty(q)) {
        printf("WARNING: Queue is empty\n");
        return NULL;
    }

    QUEUE *qP = (QUEUE *) q;

    return qP->q[qP->first].elem;
}

void destroyQueue(queue q, void (*destroyElement)()) {
    if(q == NULL) return;

    if(destroyElement != NULL)
        while(!isQueueEmpty(q))
            destroyElement(dequeue(q));
    QUEUE *qP = (QUEUE *) q;
    free(qP->q);
    free(q);
    q = NULL;
}