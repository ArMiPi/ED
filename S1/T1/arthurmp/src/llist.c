#include<stdio.h>
#include<stdlib.h>

#include"llist.h"

typedef struct _item {
    struct _item *prev;
    element elem;
    struct _item *next;
}LLITEM;

typedef struct _llist {
    LLITEM *head;
    LLITEM *tail;
}LLIST;

LLITEM *NewItem() {
    LLITEM *lli = (LLITEM *) malloc(sizeof(LLITEM));
    if(lli == NULL) {
        printf("ERROR: Could not allocate memory for new list item\n");
        exit(EXIT_FAILURE);
    }

    lli->prev = NULL;
    lli->elem = NULL;
    lli->next = NULL;

    return lli;
}

llist NewList() {
    LLIST *lst = (LLIST *) malloc(sizeof(LLIST));
    if(lst == NULL) {
        printf("ERROR: Could not allocate memory for new list\n");
        exit(EXIT_FAILURE);
    }

    lst->head = NULL;
    lst->tail = NULL;

    return lst;
}

bool IsListEmpty(llist lst) {
    if(lst == NULL) return true;

    LLIST *l = (LLIST *) lst;

    return l->head == NULL;
}

int ListSize(llist lst) {
    if(lst == NULL) return 0;

    int size = 0;

    for(item li = GetFirstItem(lst); li != NULL; li = GetNextItem(li)) size++;

    return size;
}

item InsertStart(llist lst, element elem) {
    if(lst == NULL || elem == NULL) return NULL;

    LLIST *l = (LLIST *) lst;

    // Criar novo item
    LLITEM *lli = NewItem();
    lli->elem = elem;
    lli->next = l->head;
    
    // Posicionar novo item
    if(!IsListEmpty(lst)) l->head->prev = lli;
    l->head = lli;

    // Verificar se tail == NULL
    if(l->tail == NULL) l->tail = l->head;

    return lli;
}

item InsertEnd(llist lst, element elem) {
    if(lst == NULL || elem == NULL) return NULL;

    if(IsListEmpty(lst)) return InsertStart(lst, elem);

    // Criar novo item
    LLITEM *lli = NewItem();
    lli->elem = elem;

    // Posicionar novo item
    LLITEM *last = GetLastItem(lst);
    last->next = lli;
    lli->prev = last;

    // Atualizar valor de tail
    LLIST *l = (LLIST *) lst;
    l->tail = lli;

    return lli;
}

item InsertAfter(llist lst, item li, element elem) {
    if(lst == NULL || li == NULL || elem == NULL) return NULL;

    if(GetLastItem(lst) == li) return InsertEnd(lst, elem);

    // Criar novo item
    LLITEM *lli = NewItem();
    lli->elem = elem;

    // Posicionar item
    LLITEM *llit = (LLITEM *) li;

    lli->prev = llit;
    lli->next = llit->next;

    llit->next->prev = lli;
    llit->next = lli;

    return lli;
}

item InsertBefore(llist lst, item li, element elem) {
    if(lst == NULL || li == NULL || elem == NULL) return NULL;

    if(GetFirstItem(lst) == li) return InsertStart(lst, elem);

    // Criar novo item
    LLITEM *lli = NewItem();
    lli->elem = elem;

    // Posicionar item
    LLITEM *llit = (LLITEM *) li;

    lli->next = llit;
    lli->prev = llit->prev;

    llit->prev->next = lli;
    llit->prev = lli;

    return lli;
}

element RemoveItem(llist lst, item li) {
    if(lst == NULL || li == NULL) return NULL;

    if(IsListEmpty(lst)) return NULL;

    // Armazenar elemento que deve ser retornado
    element elem = GetItemElement(li);

    // Remover elemento da lista
    LLIST *l = (LLIST *) lst;
    LLITEM *lli = (LLITEM *) li;

    if(GetFirstItem(lst) == li) l->head = l->head->next;
    if(GetLastItem(lst) == li) l->tail = l->tail->prev;
    if(lli->prev != NULL) lli->prev->next = lli->next;
    if(lli->next != NULL) lli->next->prev = lli->prev;

    lli->prev = NULL;
    lli->elem = NULL;
    lli->next = NULL;

    free(lli);

    return elem;
}

element GetItemElement(item li) {
    if(li == NULL) return NULL;

    LLITEM *lli = (LLITEM *) li;

    return lli->elem;
}

item GetFirstItem(llist lst) {
    if(lst == NULL) return NULL;

    LLIST *l = (LLIST *) lst;

    return l->head;
}

item GetLastItem(llist lst) {
    if(lst == NULL) return NULL;

    if(IsListEmpty(lst)) return NULL;

    LLIST *l = (LLIST *) lst;
    
    return l->tail;
}

item GetNextItem(item li) {
    if(li == NULL) return NULL;

    LLITEM *lli = (LLITEM *) li;

    return lli->next;
}

item GetPreviousItem(item li) {
    if(li == NULL) return NULL;

    LLITEM *lli = (LLITEM *) li;

    return lli->prev;
}

element ReplaceItem(item li, element elem) {
    if(li == NULL || elem == NULL) return NULL;

    LLITEM *lli = (LLITEM *) li;

    element toReturn = lli->elem;
    lli->elem = elem;

    return toReturn;
}

void DestroyList(llist lst, void (*destroyElement)()) {
    if(lst == NULL) return;

    if(destroyElement != NULL) {
        while(!IsListEmpty(lst)) {
            destroyElement(RemoveItem(lst, GetFirstItem(lst)));
        }
    }
    
    free(lst);
    lst = NULL;
}