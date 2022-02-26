#include<stdio.h>
#include<stdlib.h>

#include"queue.h"

typedef struct _queueItem {
    element elem;
    struct _queueItem *next;
}QUEUEITEM;

typedef struct _queue {
    QUEUEITEM *first;
}QUEUE;

/*
    # Saída:
        - QUEUEITEM: Struct
    
    # Descrição:
        - Retorna um QUEUEITEM vazio
*/
QUEUEITEM *newQueueItem() {
    QUEUEITEM *qI = (QUEUEITEM *) malloc(sizeof(QUEUEITEM));
    if(qI == NULL) {
        printf("ERROR: Could not allocate memory for queue item \n");
        exit(EXIT_FAILURE);
    }

    qI->elem = NULL;
    qI->next = NULL;

    return qI;
}

queue newQueue() {
    QUEUE *q = (QUEUE *) malloc(sizeof(QUEUE));
    if(q == NULL) {
        printf("ERROR: Could not allocate memory for queue\n");
        exit(EXIT_FAILURE);
    }

    q->first = NULL;

    return q;
}

bool isQueueEmpty(queue q) {
    if(q == NULL) return true;

    QUEUE *qu = (QUEUE *) q;

    return qu->first == NULL;
}

void enqueue(queue q, element elem) {
    if(q == NULL || elem == NULL) return;

    QUEUE *qu = (QUEUE *) q;

    // Criação do novo elemento
    QUEUEITEM *qI = newQueueItem();
    qI->elem = elem;

    /* 
        - Se q fila for vazia, o elemento será inserido em qu->first
        - Caso contrário, procurar o atual último elemento da fila e inserir
          novo elemento no final da fila
    */
    if(isQueueEmpty(q)) qu->first = qI;
    else {
        QUEUEITEM *search = qu->first;
        while(search->next != NULL) search = search->next;
        search->next = qI;
    }
}

element dequeue(queue q) {
    if(q == NULL) return NULL;

    if(isQueueEmpty(q)) {
        printf("WARNING: This queue is empty\n");
        return NULL;
    }

    QUEUE *qu = (QUEUE *) q;

    QUEUEITEM *qI = qu->first;
    element elem = qI->elem;    // Armazenar elemento armazenado na primeria posição da fila
    qu->first = qI->next;       // Atualizar o primeiro elemento da fila
    
    // Liberar a memória utilizada pelo item foi removido
    qI->elem = NULL;
    qI->next = NULL;
    free(qI);

    return elem;
}

element peekQueue(queue q) {
    if(q == NULL) return NULL;

    if(isQueueEmpty(q)) {
        printf("WARNING: This queue is empty\n");
        return NULL;
    }

    QUEUE *qu = (QUEUE *) q;

    element elem = qu->first->elem;    // Armazenar elemento armazenado na primeria posição da fila

    return elem;
}

void destroyQueue(queue q, void (*destroyElement)()) {
    if(q == NULL) return;

    if(destroyElement != NULL)
        while(!isQueueEmpty(q)) 
            destroyElement(dequeue(q));
    
    free(q);
    q = NULL;
}