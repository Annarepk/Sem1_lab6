///Implementation of the basic functions of the list

#include "list.h"
#include "change.h"
#include <stdio.h>

int main() {
    List *list = listNew();
    int inputErrorCode = input(list);
    if (inputErrorCode == 1) {
        printf("error or EOF\n");
        listDelete(list);
        return 1;
    }
    while (list) {
        printf("list: ");
        listPrint(list);

        change(list);
        printf("new list: ");
        listPrint(list);

        if (list) listDelete(list);

        list = listNew();
        inputErrorCode = input(list);
        if (inputErrorCode == 1) {
            printf("error\n");
            listDelete(list);
            return 1;
        }
    }
    return 0;
}