#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdio.h>

typedef struct Item {
    int data;
    struct Item *prev;
    struct Item *next;
} Item;


typedef struct List {
    Item *head;
    Item *tail;
} List;


List *listNew();

void listDelete(List *list);

void listPrint(const List *list);

int listInsert(List *list, int data);



List *listNew() { return (List *) calloc(1, sizeof(List)); }

void listDelete(List *list) {
    Item *ptr = list->head;
    Item *ptrPrev = NULL;
    while (ptr) {
        ptrPrev = ptr;
        ptr = ptr->next;
        free(ptrPrev);
    }
    free(list);
}

void listPrint(const List *list) {
    if (!list) {
        printf("Empty\n");
        return;
    }
    printf("\"");
    Item *ptr = list->head;
    while (ptr) {
        printf("%c", ptr->data);
        ptr = ptr->next;
    }
    printf("\"\n");
    return;
}


int listInsert(List *list, int data) {
    Item *new = (Item *) malloc(sizeof(Item));
    if (!new) return 1;

    new->data = data;
    new->next = NULL;
    new->prev = NULL;

    if (!list->head) {
        list->head = new;
        list->tail = new;
    }
    else {
        if (list->tail->prev) {
            list->tail->next = new;
            new->prev = list->tail;
            list->tail = new;
        }
        else {
            list->tail = new;
            list->head->next = new;
            list->tail->prev = list->head;
        }
    }
    return 0;
}
#endif
