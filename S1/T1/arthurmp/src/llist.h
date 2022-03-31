#ifndef LLIST_H
#define LLIST_H

#include<stdbool.h>

/*
    - Esse módulo tem por objetivo definir uma lista duplamente encadeada
      bem como funções para manupulá-la

    - Todas as funções que tiverem llist, element e/ou item como parâmetro de entrada presumem
      llist != NULL && element != NULL && item != NULL
*/

typedef void* llist;
typedef void* item;
typedef void* element;

/*
    # Saída:
        - llist: Lista
    
    # Descrição:
        - Retorna um ponteiro para uma lista vazia
*/
llist NewList();

/*
    # Entrada:
        - lst: Lista
    
    # Saída:
        - true
        - false
    
    # Descrição:
        - Retorna true se a l estiver vazia,
          false caso contrário
*/
bool IsListEmpty(llist lst);

/*
    # Entrada:
        - lst: Lista
    
    # Saída:
        - int

    # Descrição:
        - Retorna a quantidade de elementos armazenados em lst
*/
int ListSize(llist lst);

/*
    # Entradas:
        - lst: Lista
        - elem: Elemento
    
    # Saída:
        - item: Struct

    # Descrição:
        - Insere elem no início da lista

        - Retorna um ponteiro para o item que foi 
          inserido na lista
*/
item InsertStart(llist lst, element elem);

/*
    # Entradas:
        - lst: Lista
        - elem: Elemento
    
    # Saída:
        - item: Struct

    # Descrição:
        - Insere elem no final da lista

        - Retorna um ponteiro para o item que foi 
          inserido na lista
        
        - Se isListEmpty(lst) será executada a função
          insertStart()
*/
item InsertEnd(llist lst, element elem);

/*
    # Entradas:
        - lst: Lista
        - li: Item da lista
        - elem: Elemento
    
    # Saída:
        - item: Struct

    # Descrição:
        - Insere elem após o item li da lista

        - Retorna um ponteiro para o item que foi 
          inserido na lista
*/
item InsertAfter(llist lst, item li, element elem);

/*
    # Entradas:
        - lst: Lista
        - li: Item da lista
        - elem: Elemento
    
    # Saída:
        - item: Struct

    # Descrição:
        - Insere elem antes o item li da lista

        - Retorna um ponteiro para o item que foi 
          inserido na lista
*/
item InsertBefore(llist lst, item li, element elem);

/*
    # Entradas:
        - lst: Lista
        - li: Item
    
    # Saída:
        - element
    
    # Descrição:
        - Remove o item li da lista e retorna o
          elemento elem armazenado nesse item

        - Se a lista estiver vazia será retornado
          NULL
*/
element RemoveItem(llist lst, item li);

/*
    # Entrada:
        - li: Item
    
    # Saída:
        - element
    
    # Descrição:
        - Retorna o elemento element 
          armazenado em li
*/
element GetItemElement(item li);

/*
    # Entrada:
        - lst: Lista
    
    # Saída:
        - item: Struct
    
    # Descrição:
        - Retorna um ponteiro para o primeiro
          item da lista
        
        - Se a lista for vazia será retornado NULL
*/
item GetFirstItem(llist lst);

/*
    # Entrada:
        - lst: Lista
    
    # Saída:
        - item: Struct
    
    # Descrição:
        - Retorna um ponteiro para o último
          item da lista

        - Se a lista for vazia será retornado NULL
*/
item GetLastItem(llist lst);

/*
    # Entradas:
        - li: Item
    
    # Saída:
        - item
    
    # Descrição:
        - Retorna o próximo item da lista
*/
item GetNextItem(item li);

/*
    # Entradas:
        - li: Item
    
    # Saída:
        - item
    
    # Descrição:
        - Retorna o item da lista anterior a li
*/
item GetPreviousItem(item li);

/*
    # Entradas:
        - li: Item da lista
        - elem: Elemento

    # Saída:
        - elem: Elemento
    
    # Descrição:
        - Substitui o elemento armazenado em li por elem e retorna
          o elemento que foi substituído
*/
element ReplaceItem(item li, element elem);

/*
    # Entradas:
        - lst: Lista
        - destroyElement: Função
    
    # Descrição:
        - Libera toda a memória utilizada por l

        - Se destroyElement == NULL os elements de
          l não terão seus espaços de memória deslocados
*/
void DestroyList(llist lst, void (*destroyElement)());

#endif