#ifndef STACK_H
#define STACK_H

#include<stdbool.h>

/*
    - Esse módulo tem por objetivo implementar um tipo stack (pilha),
      bem como funções para manipular esse tipo
    
    - Em todas as funções stack e element, como parâmetros de entrada,
      devem ser != NULL
*/

typedef void* stack;
typedef void* element;

/*
    # Saída:
        - stack: Struct
    
    # Descrição:
        - Retorna um ponteiro para uma instância de stack contendo
          uma pilha vazia
        
        - É necessário liberar a memória utilizada pelo retorno dessa função
*/
stack newStack();

/*
    # Entrada:
        - stk: Pilha

    # Saídas:
        - true
        - false
    
    # Descrição:
        - Retorna true se stk for uma stack vazia,
          false caso contrário
*/
bool isStackEmpty(stack stk);

/*
    # Entrada:
        - stk: Pilha

    # Saídas:
        - true
        - false
    
    # Descrição:
        - Retorna true se stk for uma stack cheia,
          false caso contrário
*/
bool isStackFull(stack stk);

/*
    # Entradas:
        - stk: Pilha
        - elem: Elemento
    
    # Descrição:
        - Adiciona elem ao topo do fila
*/
void push(stack stk, element elem);

/*
    # Entrada:
        - stk: Pilha
    
    # Saída:
        - element
        - NULL
    
    # Descrição:
        - Remove o elemento element que está
          no topo de stk
        
        - Se isStackEmpty(stk) == true será
          retornado NULL
*/
element pop(stack stk);

/*
    # Entrada:
        - stk: Pilha
    
    # Saída:
        - element
    
    # Descrição:
        - Retorna o elemento no topo de stk,
          sem removê-lo
*/
element peekStack(stack stk);

/*
    # Entrada:
        - stk: Pilha
        - destroyElement: Ponteiro para função para
          liberar a memória utilizada por element
    
    # Descrição:
        - Libera toda a memória utilizada por stk

        - Se destroyElement == NULL os elements de
          stk não terão seus espaços de memória deslocados
*/
void destroyStack(stack stk, void (*destroyElement)());

#endif