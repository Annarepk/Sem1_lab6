#ifndef CHANGE_H
#define CHANGE_H

#include "list.h"
#include <stdio.h>
#include <stdlib.h>


int input(List *list);

int change(List *list);



int input(List *list) {
    printf("Enter string: ");
    int flag = 1, letter = getchar();

    while (letter != 10 && letter != -1) {
        if (((letter >= 65) && (letter <= 91)) || ((letter >= 97) && (letter <= 122))) {
            flag = 0;
            if (listInsert(list, letter) == 1) return 1;
        }
        else if (flag == 0){
            flag = 1;
            if (listInsert(list, 32) == 1) return 1;
        }
        letter = getchar();
    }
    if (letter == -1) {
        printf("EOF\n");
        return 1;
    }
    return 0;
}


int change(List *list) {
    Item *ptr = list->head;
    Item *ptrAlpha = ptr;
    Item *ptrPrevFirst = NULL;
    Item *it = ptr;     // элемент для иттерации в while
    int alpha = 0;

    while (ptrAlpha) {  // нашли нужную букву
        if (ptrAlpha->prev && ptrAlpha->prev->data == 32) alpha = ptrAlpha->data;
        ptrAlpha = ptrAlpha->next;
    }

    while (ptr) {
        if (ptr->prev && ptr->prev->data == 32) ptrPrevFirst = ptr;     // запоминаем начало слова

        if (ptr->data == 32 && ptr->prev->data == alpha) {      // если последняя буква - нужная
            it = ptr->next;
            if (ptrPrevFirst) {
                // вырезаем слово из списка
                ptrPrevFirst->prev->next = ptr->next;
                ptr->next->prev = ptrPrevFirst->prev;

                // вставляем слово в начало
                ptr->next = list->head;
                list->head->prev = ptr;
                list->head = ptrPrevFirst;
            }
            ptr = it;
        }
        else if (!ptr->next && ptr->data == alpha) {    // проверяем последнее слово строки
            if (ptrPrevFirst) {
                Item *space = (Item *) malloc(sizeof(Item));
                if (!space) return 1;
                space->data = 32;
                space->next = list->head;
                space->prev = ptr;

                ptr->next = space;
                list->head->prev = space;
                list->head = ptrPrevFirst;
                list->tail = ptrPrevFirst->prev->prev;    // убираем лишний пробел в конце строки
                free(ptrPrevFirst->prev);
                list->tail->next = NULL;
            }
            ptr = NULL;
        }
        else ptr = ptr->next;
    }
    return 0;
}

#endif