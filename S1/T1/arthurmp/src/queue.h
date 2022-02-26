#ifndef QUEUE_H
#define QUEUE_H

#include<stdbool.h>

/*
    - Esse módulo tem por objetivo definir um tipo queue (fila),
      bem como funções para manipular esse tipo

    - Todas as funções que possuem queue e/ou element como parâmetro de entrada
      pressupõem queue != NULL && element != NULL
*/

typedef void* queue;
typedef void* element;

/*
    # Saída:
        - queue: Struct
    
    # Descrição:
        - Retorna um ponteiro para uma fila vazia

        - É necessário liberar a memória utilizada pelo retorno dessa função
*/
queue newQueue();

/*
    # Entrada:
        - q: Fila
    
    # Saídas:
        - true
        - false
    
    # Descrição:
        - Retorna true se q for vazia,
          false caso contrário
*/
bool isQueueEmpty(queue q);

/*
    # Entradas:
        - q: Fila
        - elem: Elemento
    
    # Descrição:
        - Insere elem no final de q
*/
void enqueue(queue q, element elem);

/*
    # Entrada:
        - q: Fila
    
    # Saída:
        - element
    
    # Descrição:
        - Retorna o primeiro elemento da fila e
          o remove da mesma
        
        - Se isQueueEmpt(q) == true, será retornado NULL
*/
element dequeue(queue q);

/*
    # Entrada:
        - q: Fila
    
    # Saída:
        - element
    
    # Descrição:
        - Retorna o primeiro elemento da fila
          sem removê-lo
        
        - Se isQueueEmpt(q) == true, será retornado NULL
*/
element peekQueue(queue q);

/*
    # Entrada:
        - q: Fila
        - destroyElement: Ponteiro para função para
          liberar a memória utilizada por element
    
    # Descrição:
        - Libera toda a memória utilizada por q

        - Se destroyElement == NULL os elements de
          q não terão seus espaços de memória deslocados
*/
void destroyQueue(queue q, void (*destroyElement)());

#endif