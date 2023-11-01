/* ******************************* c206.c *********************************** */
/*  Course: Algorithms (IAL) - FIT VUT in Brno                               */
/*  Task: c206 - Doubly Linked Linear List                                    */
/*  Design and reference implementation: Bohuslav Křena, October 2001         */
/*  Created by: Martin Tuček, October 2004                                    */
/*  Modified by: Kamil Jeřábek, September 2020                                */
/*              Daniel Dolejška, September 2021                               */
/* ************************************************************************** */
/*
** Implement the abstract data type doubly linked linear list.
** The useful content of the list item is an int type value. The list will be, as a data
** abstraction, represented by a variable of type DLList (DL stands for Doubly-Linked
** and serves to distinguish the names of constants, types, and functions from the names of singly
** linked linear list). You will find the definition of constants and types
** in the header file c206.h.
**
** Your task is to implement the following operations, which together with the above
** mentioned data part of the abstraction form the abstract data type of a doubly
** linked linear list:
**
**      DLL_Init ........... list initialization before its first use,
**      DLL_Dispose ........ dispose of all list items,
**      DLL_InsertFirst .... insert an item at the beginning of the list,
**      DLL_InsertLast ..... insert an item at the end of the list,
**      DLL_First .......... set the activity to the first item,
**      DLL_Last ........... set the activity to the last item,
**      DLL_GetFirst ....... returns the value of the first item,
**      DLL_GetLast ........ returns the value of the last item,
**      DLL_DeleteFirst .... deletes the first item from the list,
**      DLL_DeleteLast ..... deletes the last item from the list,
**      DLL_DeleteAfter .... deletes the item after the active item,
**      DLL_DeleteBefore ... deletes the item before the active item,
**      DLL_InsertAfter .... inserts a new item after the active item in the list,
**      DLL_InsertBefore ... inserts a new item before the active item in the list,
**      DLL_GetValue ....... returns the value of the active item,
**      DLL_SetValue ....... overwrites the content of the active item with a new value,
**      DLL_Previous ....... moves activity to the previous list item,
**      DLL_Next ........... moves activity to the next list item,
**      DLL_IsActive ....... determines the activity of the list.
**
** When implementing individual functions, do not call any of the functions
** implemented within this example unless explicitly mentioned otherwise.
**
** You don't need to handle the situation where someone passes a NULL value as a parameter 
** instead of a legitimate pointer to the list.
**
** Comment on your implementation appropriately!
**
** Terminology note: The C language does not use the term procedure.
** Therefore, here we use the term function even for operations that would be
** implemented as procedures in an algorithmic language of the Pascal type
** (in the C language, procedures correspond to functions returning the void type).
**
**/

#include "c206.h"

int error_flag;
int solved;

/**
 * Prints a warning that an error has occurred.
 * This function will be called from some of the later implemented operations.
 */
void DLL_Error() {
    printf("*ERROR* The program has performed an illegal operation.\n");
    error_flag = TRUE;
}

/**
 * Initializes the list before its first use (i.e., none
 * of the following functions will be called on an uninitialized list).
 * This initialization will never be done on an already initialized list,
 * so do not handle this possibility.
 * Always assume that uninitialized variables have an undefined value.
 *
 * @param list Pointer to the doubly linked list structure
 */
void DLL_Init(DLList *list) {

    list->firstElement = NULL;
    list->activeElement = NULL;
    list->lastElement = NULL;
}

/**
 * Deletes all elements of the list and puts the list in the state it was in
 * after initialization.
 * The deleted list elements will be correctly freed by calling the free operation.
 *
 * @param list Pointer to the initialized doubly linked list structure
 */
void DLL_Dispose(DLList *list) {

    while (list->firstElement != NULL) {
        DLL_DeleteFirst(list);
    }
    DLL_Init(list);
}

/**
 * Inserts a new element at the beginning of the list.
 * If there is not enough memory for the new element during the malloc operation,
 * it calls the DLL_Error() function.
 *
 * @param list Pointer to the initialized doubly linked list structure
 * @param data Value to be inserted at the beginning of the list
 */
void DLL_InsertFirst(DLList *list, int data) {

    DLLElementPtr newElement = (DLLElementPtr) malloc(sizeof(struct DLLElement));
    if (newElement == NULL) {
        DLL_Error();
        return;
    }
    newElement->data = data;

    newElement->previousElement = NULL;
    newElement->nextElement = list->firstElement;

    // If an element was already in the list
    if (list->firstElement != NULL) {
        list->firstElement->previousElement = newElement;
    }

    list->firstElement = newElement;

    // If it is the first element, it is also the last
    if (list->lastElement == NULL) {
        list->lastElement = newElement;
    }
}

/**
 * Inserts a new element at the end of the list (symmetric operation to DLL_InsertFirst).
 * If there is not enough memory for the new element during the malloc operation,
 * it calls the DLL_Error() function.
 *
 * @param list Pointer to the initialized doubly linked list structure
 * @param data Value to be inserted at the end of the list
 */
void DLL_InsertLast(DLList *list, int data) {

    DLLElementPtr newElement = (DLLElementPtr) malloc(sizeof(struct DLLElement));
    if (newElement == NULL) {
        DLL_Error();
        return;
    }
    newElement->data = data;

    newElement->nextElement = NULL;
    newElement->previousElement = list->lastElement;

    // If there are already some elements in the list
    if (list->lastElement != NULL) {

        list->lastElement->nextElement = newElement;
    }
    list->lastElement = newElement;

    if (list->firstElement == NULL) {
        list->firstElement = newElement;
    }
}

/**
 * Sets the first element of the list as active.
 * Implement the function as a single command (not counting return),
 * without testing whether the list is empty.
 *
 * @param list Pointer to the initialized doubly linked list structure
 */
void DLL_First(DLList *list) {

    list->activeElement = list->firstElement;
}

/**
 * Sets the last element of the list as active.
 * Implement the function as a single command (not counting return),
 * without testing whether the list is empty.
 *
 * @param list Pointer to the initialized doubly linked list structure
 */
void DLL_Last(DLList *list) {

    list->activeElement = list->lastElement;
}

/**
 * Returns the value of the first element of the list through the dataPtr parameter.
 * If the list is empty, it calls the DLL_Error() function.
 *
 * @param list Pointer to the initialized doubly linked list structure
 * @param dataPtr Pointer to the target variable
 */
void DLL_GetFirst(DLList *list, int *dataPtr) {

    if (list->firstElement == NULL) {
        DLL_Error();
    } else {
        *dataPtr = list->firstElement->data;
    }
}

/**
 * Returns the value of the last element of the list through the dataPtr parameter.
 * If the list is empty, it calls the DLL_Error() function.
 *
 * @param list Pointer to the initialized doubly linked list structure
 * @param dataPtr Pointer to the target variable
 */
void DLL_GetLast(DLList *list, int *dataPtr) {

    if (list->lastElement == NULL) {
        DLL_Error();
        return;
    } else {
        *dataPtr = list->lastElement->data;
    }
}

/**
 * Deletes the first element of the list.
 * If the first element was active, activity is lost.
 * If the list was empty, nothing happens.
 *
 * @param list Pointer to the initialized doubly linked list structure
 */
void DLL_DeleteFirst(DLList *list) {

    if (list->firstElement == NULL) {
        return;
    }

    // Cancellation of possible activity
    if (list->activeElement == list->firstElement) {
        list->activeElement = NULL;
    }

    DLLElementPtr element = list->firstElement;
    list->firstElement = element->nextElement;
    // If the new first element is not NULL, change the pointer to the ancestor
    if (list->firstElement != NULL) {
        list->firstElement->previousElement = NULL;
    }

    // If the element was also the last
    if (element == list->lastElement) {
        list->firstElement = NULL;
        list->lastElement = NULL;
    }

    free(element);
}

/**
 * Deletes the last element of the list.
 * If the last element was active, activity is lost.
 * If the list was empty, nothing happens.
 *
 * @param list Pointer to the initialized doubly linked list structure
 */
void DLL_DeleteLast(DLList *list) {

    // If the list is empty, we do nothing
    if (list->lastElement == NULL) {
        return;
    } else {
        // Cancellation of possible activity
        if (list->activeElement == list->lastElement) {
            list->activeElement = NULL;
        }

        DLLElementPtr element = list->lastElement;

        // If the element was also the last
        if (element == list->firstElement) {
            list->firstElement = NULL;
            list->lastElement = NULL;
        } else {
            list->lastElement = element->previousElement;
            list->lastElement->nextElement = NULL;
        }

        free(element);
    }
}

/**
 * Deletes the element in the list 'list' after the active element.
 * If the list 'list' is inactive or if the active element
 * is the last element of the list, nothing happens.
 *
 * @param list Pointer to the initialized structure of a doubly linked list
 */
void DLL_DeleteAfter(DLList *list) {

    if (!DLL_IsActive(list)) {
        return;
    }
    if (list->activeElement->nextElement == NULL) {
        return;
    }

    DLLElementPtr element = list->activeElement->nextElement;
    list->activeElement->nextElement = element->nextElement;
    // If the element we are deleting is not the last one
    if (element->nextElement != NULL) {
        element->nextElement->previousElement = list->activeElement;
    }
    // If last, change the pointer to the last element
    else {
        list->lastElement = list->activeElement;
    }

    free(element);
}

/**
 * Deletes the element in the list 'list' before the active element.
 * If the list 'list' is inactive or if the active element
 * is the first element of the list, nothing happens.
 *
 * @param list Pointer to the initialized structure of a doubly linked list
 */
void DLL_DeleteBefore(DLList *list) {

    if (!DLL_IsActive(list)) {
        return;
    }
    if (list->activeElement == list->firstElement) {
        return;
    }

    DLLElementPtr element = list->activeElement->previousElement;
    list->activeElement->previousElement = element->previousElement;

    // If the element we are removing is the first
    if (element->previousElement != NULL) {
        element->previousElement->nextElement = list->activeElement;
    } else {
        list->firstElement = list->activeElement;
    }

    free(element);
}

/**
 * Inserts an element after the active element in the list 'list'.
 * If the list 'list' was inactive, nothing happens.
 * In case there's not enough memory for a new element during the malloc operation,
 * it calls the DLL_Error() function.
 *
 * @param list Pointer to the initialized structure of a doubly linked list
 * @param data Value to insert into the list after the currently active element
 */
void DLL_InsertAfter(DLList *list, int data) {

    if (!DLL_IsActive(list)) {
        return;
    }

    DLLElementPtr newElement = (DLLElementPtr) malloc(sizeof(struct DLLElement));
    if (newElement == NULL) {
        DLL_Error();
    }

    newElement->data = data;
    // Linking the new item with the item after the active item
    newElement->nextElement = list->activeElement->nextElement;
    if (list->activeElement->nextElement != NULL) {
        list->activeElement->nextElement->previousElement = newElement;
    }
    // Linking of the new item with the active item
    newElement->previousElement = list->activeElement;
    list->activeElement->nextElement = newElement;

    // If the active item was also the last
    if (list->activeElement == list->lastElement) {
        list->lastElement = newElement;
    }
}

/**
 * Inserts an element before the active element in the list 'list'.
 * If the list 'list' was inactive, nothing happens.
 * In case there's not enough memory for a new element during the malloc operation,
 * it calls the DLL_Error() function.
 *
 * @param list Pointer to the initialized structure of a doubly linked list
 * @param data Value to insert into the list before the currently active element
 */
void DLL_InsertBefore(DLList *list, int data) {

    if (!DLL_IsActive(list)) {
        return;
    }

    DLLElementPtr newElement = (DLLElementPtr) malloc(sizeof(struct DLLElement));
    if (newElement == NULL) {
        DLL_Error();
    }

    newElement->data = data;
    // Linking of the new element with its surroundings
    newElement->nextElement = list->activeElement;
    newElement->previousElement = list->activeElement->previousElement;
    // Linking the environment with the new element
    if (list->activeElement->previousElement != NULL) {
        list->activeElement->previousElement->nextElement = newElement;
    }
    list->activeElement->previousElement = newElement;

    // If the active element was also the first
    if (list->activeElement == list->firstElement) {
        list->firstElement = newElement;
    }
}

/**
 * Returns the value of the active element of the list 'list' through the dataPtr parameter.
 * If the list 'list' is not active, it calls the DLL_Error() function.
 *
 * @param list Pointer to the initialized structure of a doubly linked list
 * @param dataPtr Pointer to the target variable
 */
void DLL_GetValue(DLList *list, int *dataPtr) {

    if (list->activeElement == NULL) {
        DLL_Error();
    } else {
        *dataPtr = list->activeElement->data;
    }
}

/**
 * Overwrites the content of the active element in the list 'list'.
 * If the list 'list' is not active, it does nothing.
 *
 * @param list Pointer to the initialized structure of a doubly linked list
 * @param data New value of the currently active element
 */
void DLL_SetValue(DLList *list, int data) {

    if (list->activeElement != NULL) {
        list->activeElement->data = data;
    }
}

/**
 * Moves the activity to the next element of the list 'list'.
 * If the list is not active, it does nothing.
 * Note that when active on the last element, the list becomes inactive.
 *
 * @param list Pointer to the initialized structure of a doubly linked list
 */
void DLL_Next(DLList *list) {

    if (list->activeElement != NULL) {
        list->activeElement = list->activeElement->nextElement;
    }
}


/**
 * Moves the activity to the previous element of the list 'list'.
 * If the list is not active, it does nothing.
 * Note that when active on the first element, the list becomes inactive.
 *
 * @param list Pointer to the initialized structure of a doubly linked list
 */
void DLL_Previous(DLList *list) {

    if (list->activeElement != NULL) {
        list->activeElement = list->activeElement->previousElement;
    }
}

/**
 * If the list 'list' is active, it returns a non-zero value, otherwise it returns 0.
 * It's suitable to implement this function with a single return command.
 *
 * @param list Pointer to the initialized structure of a doubly linked list
 *
 * @returns A non-zero value in case of activity of the list element, otherwise zero
 */
int DLL_IsActive(DLList *list) {

    return (list->activeElement != NULL);
}

/* End of c206.c */
