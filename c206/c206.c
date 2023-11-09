/**
 * @file c206.c
 * @brief Implementation of the Doubly Linked Linear List.
 * @details This file defines the abstract data type of a doubly linked linear list
 *          with operations to manipulate the list. It includes functions to initialize,
 *          dispose, insert, delete, and provide various controls over list items.
 * 
 * @note Add any specific notes here if needed.
 * 
 * @code
 * // Example usage:
 * DLList list;
 * DLLInit(&list);
 * // Additional operations
 * DLLDispose(&list);
 * @endcode
 * 
 * @see c206.h for definition of constants and types.
 * 
 * @author Bohuslav Křena (design and reference implementation),
 *         Martin Tuček (creator),
 *         Kamil Jeřábek (editor),
 *         Daniel Dolejška (editor),
 *         Evgenii Shiliaev (solution author)
 * @date October 2001 (design and reference implementation),
 *       October 2004 (creation),
 *       September 2020 (edit),
 *       September 2021 (latest edit)
 *       October 2021 (solution)
 *       November 2023 (code comments updated)
 */

#include "c206.h"

int error_flag;
int solved;

/**
 * @brief Reports an illegal operation error in doubly linked list operations.
 * 
 * @details This function outputs an error message to the standard console indicating
 *          that an illegal operation has been attempted. It also sets an internal
 *          error flag to TRUE. This function is intended to be called from other
 *          operations within the doubly linked list implementation when they encounter
 *          an error.
 * 
 * @note The function assumes that standard output is available and writable. The actual
 *       handling of the error after setting the flag is dependent on the implementation
 *       of the calling code.
 * 
 * @todo Implement a more sophisticated error reporting mechanism that can provide
 *       more details about the error context and potential recovery strategies.
 * 
 * @warning This function should only be called when an actual error condition is
 *          detected as it will modify the state of the error flag.
 * 
 * @return This function does not return a value.
 */
void DLL_Error() {
    printf("*ERROR* The program has performed an illegal operation.\n");
    error_flag = TRUE;
}

/**
 * @brief Initializes the doubly linked list.
 * 
 * @details This function sets up the necessary structure for a doubly linked list by
 *          initializing all pointers within the DLList structure to NULL, indicating
 *          an empty list state. This is a mandatory step before the list can be used
 *          with other list operations.
 * 
 * @param list Pointer to the doubly linked list structure to be initialized.
 * 
 * @pre The list should not have been previously initialized as this function does not
 *      handle reinitialization.
 * 
 * @post The list is in a state where other doubly linked list functions can be safely
 *       called. All the internal pointers of the list (firstElement, activeElement,
 *       and lastElement) are set to NULL.
 * 
 * @note The caller must ensure that the list is not already initialized since this
 *       function does not handle reinitialization. It is also assumed that the list
 *       structure is not NULL.
 * 
 * @code
 *   DLList myList;
 *   DLL_Init(&myList);
 * @endcode
 * 
 * @todo In future revisions, consider adding checks to prevent reinitialization of the list
 *       or defining a separate function to reinitialize the list if needed.
 * 
 * @warning Do not call this function on an already initialized list as it will not
 *          check for or handle such a condition.
 * 
 * @return This function does not return a value.
 */
void DLL_Init(DLList *list) {

    list->firstElement = NULL;
    list->activeElement = NULL;
    list->lastElement = NULL;
}

/**
 * @brief Deletes all elements from the doubly linked list and reinitializes it.
 * 
 * @details Iterates over the list and removes each element, starting from the first.
 *          After all elements are deleted, it calls DLL_Init to reset the list
 *          to its initial state with all internal pointers set to NULL.
 *
 * @param list Pointer to the initialized doubly linked list structure to be cleared.
 * 
 * @pre The list must be previously initialized. This function should not be called
 *      on an uninitialized or NULL list pointer.
 * 
 * @post The list is empty and reset to the same state as it was immediately after
 *       a call to DLL_Init, with no active elements and all pointers set to NULL.
 * 
 * @note Assumes that DLL_DeleteFirst and DLL_Init functions are correctly implemented
 *       and do not cause memory leaks or dangling pointers.
 * 
 * @code
 * DLList myList;
 * DLL_Init(&myList);
 * // [Code to add elements to myList]
 * DLL_Dispose(&myList); // Disposes of the list and reinitializes it
 * @endcode
 * 
 * @todo Implement additional error checking to handle potential issues with list deletion.
 * 
 * @warning Calling this function on an uninitialized or NULL list pointer will lead to
 *          undefined behavior.
 * 
 * @return This function does not return a value.
 */
void DLL_Dispose(DLList *list) {

    while (list->firstElement != NULL) {
        DLL_DeleteFirst(list);
    }
    DLL_Init(list);
}

/**
 * @brief Inserts a new element at the beginning of the list.
 * 
 * @details This function creates a new list element with the given data and 
 *          inserts it at the start of the list. If memory allocation for the 
 *          new element fails, the error handling function is called.
 * 
 * @param list Pointer to the initialized doubly linked list structure.
 * @param data Value to be inserted at the beginning of the list.
 * 
 * @pre The 'list' must be a valid, initialized doubly linked list.
 * 
 * @post If successful, the new element is placed at the beginning of the list.
 *       If the list was empty, the new element is also the last element.
 *       If memory allocation fails, the error is handled and the function exits.
 * 
 * @note The function assumes the existence of a corresponding error handling 
 *       function DLL_Error to manage memory allocation failures.
 * 
 * @code
 *   DLList myList;
 *   DLL_Init(&myList);
 *   DLL_InsertFirst(&myList, 10); // Inserting 10 at the beginning of the list
 *   DLL_First(&myList);           // Setting the first element (10) as active
 * @endcode
 *  
 * @todo Improve memory management to handle low-memory situations more gracefully.
 * 
 * @warning If memory allocation fails, the state of the list does not change, but 
 *          the error handling function is invoked which may affect program state.
 * 
 * @return This function does not return a value.
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
 * @brief Inserts a new element at the end of the list.
 * 
 * @details This function appends a new element with the specified data to the end of the list.
 *          If memory cannot be allocated for the new element, the DLL_Error() function is invoked.
 * 
 * @param list Pointer to the initialized doubly linked list structure.
 * @param data Value to be inserted at the end of the list.
 * 
 * @pre The 'list' must be a valid, initialized doubly linked list.
 * 
 * @post The new element is added to the end of the list. If the list was empty,
 *       the new element becomes both the first and last element of the list.
 * 
 * @note This function is the symmetric counterpart to DLL_InsertFirst and assumes
 *       that memory can be allocated for the new element.
 * 
 * @code
 *   DLList myList;
 *   DLL_Init(&myList);
 *   DLL_InsertFirst(&myList, 10); // Inserting 10 at the beginning of the list
 *   DLL_InsertLast(&myList, 20);  // Inserting 20 at the end of the list
 *   DLL_Last(&myList);            // Setting the last element (20) as active
 * @endcode
 * 
 * @todo Implement a return value to indicate the success of the operation.
 * 
 * @warning If memory allocation fails, the DLL_Error() function will be triggered,
 *          which may change the program's state or halt execution.
 * 
 * @return This function does not return a value.
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
 * @brief Sets the first element of the list as active.
 * 
 * @details This function marks the first element in the list as active, allowing operations
 *          to be performed on this element. The function does not check if the list is empty
 *          and directly sets the active element pointer to the first element.
 * 
 * @param list Pointer to the initialized doubly linked list structure.
 * 
 * @pre The list must be initialized before calling this function. The function does not
 *      check for an empty list, so 'list' should not be empty to avoid undefined behavior.
 * 
 * @post The 'activeElement' pointer in the list points to the first element, making it
 *       the current element for subsequent operations.
 * 
 * @note This function is implemented as a single command to optimize performance.
 * 
 * @code
 *   DLList myList;
 *   DLL_Init(&myList);
 *   DLL_InsertFirst(&myList, 10); // Inserting 10 at the beginning of the list
 *   DLL_First(&myList);           // Setting the first element (10) as active
 * @endcode
 * 
 * @todo Consider adding a check for an empty list and appropriate handling if needed.
 * 
 * @warning Since the function does not check for an empty list, calling this function
 *          on an empty list could lead to subsequent undefined behavior if the active
 *          element is accessed.
 * 
 * @return This function does not return a value.
 */
void DLL_First(DLList *list) {

    list->activeElement = list->firstElement;
}

/**
 * @brief Sets the last element of the list as active.
 * 
 * @details Activates the last element in the list, which allows subsequent operations
 *          to be performed on it. The function does not perform an emptiness check
 *          and will directly set the active element to the last element.
 * 
 * @param list Pointer to the initialized doubly linked list structure.
 * 
 * @pre The 'list' must be initialized before this function is invoked. The list
 *      should not be empty to ensure the active element is valid.
 * 
 * @post The 'activeElement' of the list is set to the last element. If subsequent
 *       operations are called on the active element, they will be performed on
 *       this last element.
 * 
 * @note The function assumes that the list is not empty and that the last element
 *       is a valid element to be activated.
 * 
 * @code
 *   DLList myList;
 *   DLL_Init(&myList);
 *   DLL_InsertFirst(&myList, 10); // Inserting 10 at the beginning of the list
 *   DLL_InsertLast(&myList, 20);  // Inserting 20 at the end of the list
 *   DLL_Last(&myList);            // Setting the last element (20) as active
 * @endcode
 * 
 * @todo Future implementations could include safety checks to handle empty lists.
 * 
 * @warning Without an emptiness check, setting an active element on an empty list
 *          could lead to undefined behavior during subsequent operations.
 * 
 * @return This function does not return a value.
 */
void DLL_Last(DLList *list) {

    list->activeElement = list->lastElement;
}

/**
 * @brief Retrieves the value of the first element in the list.
 * 
 * @details If the list is not empty, the value of the first element is returned through
 *          the dataPtr parameter. If the list is empty, the DLL_Error() function is called.
 * 
 * @param list Pointer to the initialized doubly linked list structure.
 * @param dataPtr Pointer to the target variable where the value of the first element will be stored.
 * 
 * @pre The 'list' should be initialized and 'dataPtr' must be a valid pointer to an integer.
 *      The list should not be empty to ensure a value can be retrieved.
 * 
 * @post If the list is not empty, the value of the first element is stored in the variable
 *       pointed to by dataPtr. If the list is empty, an error function is invoked and the
 *       value at dataPtr remains unchanged.
 * 
 * @note This function assumes that DLL_Error() is defined and correctly handles error reporting.
 * 
 * @code
 *   DLList myList;
 *   DLL_Init(&myList);
 *   DLL_InsertFirst(&myList, 10);
 *   DLL_InsertFirst(&myList, 20);
 *   int firstValue = DLL_GetFirst(&myList); // Retrieves value of the first element (20)
 *   printf("First element value: %d\n", firstValue);
 * @endcode
 * 
 * @todo Consider changing the function to return a status code that indicates success or failure.
 * 
 * @warning If the list is empty, the function does not modify the value at dataPtr and
 *          calls DLL_Error() which may affect the program's state.
 * 
 * @return This function does not return a value.
 */
void DLL_GetFirst(DLList *list, int *dataPtr) {

    if (list->firstElement == NULL) {
        DLL_Error();
    } else {
        *dataPtr = list->firstElement->data;
    }
}

/**
 * @brief Returns the value of the last element in the doubly linked list.
 * 
 * @details The function retrieves the data of the last element and passes it back through 
 *          the dataPtr parameter. If the list is empty, the error handling function DLL_Error() 
 *          is called to indicate the issue.
 * 
 * @param list Pointer to the initialized doubly linked list structure.
 * @param dataPtr Pointer to the target variable where the value of the last element will be stored.
 * 
 * @pre The 'list' should be initialized before calling this function. The 'dataPtr' should 
 *      point to a valid integer that can store the retrieved value.
 * 
 * @post If the list is not empty, 'dataPtr' is set to the value of the last element. If the 
 *       list is empty, DLL_Error() is called, and no value is set.
 * 
 * @note It is assumed that the list structure is properly maintained and that the DLL_Error() 
 *       function is implemented to handle error conditions.
 * 
 * @code
 *   DLList myList;
 *   DLL_Init(&myList);
 *   DLL_InsertLast(&myList, 10);
 *   DLL_InsertLast(&myList, 20);
 *   int lastValue = DLL_GetLast(&myList); // Retrieves value of the last element (20)
 *   printf("Last element value: %d\n", lastValue);
 * @endcode
 * 
 * @todo Implement additional error handling or return a status code to indicate the success 
 *       of the operation.
 * 
 * @warning If the list is empty, calling this function will result in an error, and the 
 *          'dataPtr' will not be updated.
 * 
 * @return This function does not return a value.
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
 * @brief Deletes the first element of the doubly linked list.
 * 
 * @details Removes the first element from the list. If the first element is also
 *          the active element, the activity of the list is canceled. If the list
 *          is empty, the function performs no action.
 * 
 * @param list Pointer to the initialized doubly linked list structure.
 * 
 * @pre The 'list' must be initialized before calling this function. The behavior is
 *      undefined if 'list' is uninitialized or NULL.
 * 
 * @post The first element is removed from the list. If the list was not empty, the
 *       pointers are adjusted to maintain list integrity. If the removed element was
 *       also the active element, the activity is canceled. If the list is empty,
 *       the state of the list is unchanged.
 * 
 * @note This function handles the deallocation of memory for the removed element.
 * 
 * @code
 *   DLList myList;
 *   DLL_Init(&myList);
 *   DLL_InsertFirst(&myList, 10);
 *   DLL_InsertFirst(&myList, 20);
 *   DLL_DeleteFirst(&myList); // After this, 10 is the first element
 * @endcode
 * 
 * @todo For future implementation, consider returning a status to indicate the result
 *       of the deletion operation.
 * 
 * @warning If the list is empty, the function exits without performing any operations.
 * 
 * @return This function does not return a value.
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
 * @brief Deletes the last element of the doubly linked list.
 * 
 * @details If the list is not empty, this function removes the last element. If the
 *          last element is also the active element, the activity of the list is canceled.
 *          If the list is empty, the function does not perform any action.
 * 
 * @param list Pointer to the initialized doubly linked list structure.
 * 
 * @pre The 'list' should be initialized before calling this function. The behavior is
 *      undefined if 'list' is uninitialized or NULL.
 * 
 * @post The last element is removed from the list. If the list was not empty, the
 *       pointers are adjusted accordingly. If the removed element was the active element,
 *       the activity is canceled. If the list is empty, the state of the list is unchanged.
 * 
 * @note This function takes care of deallocating memory for the removed element.
 * 
 * @code
 *   DLList myList;
 *   DLL_Init(&myList);
 *   DLL_InsertLast(&myList, 10);
 *   DLL_InsertLast(&myList, 20);
 *   DLL_DeleteLast(&myList); // After this, 10 is the last element
 * @endcode
 * 
 * @todo In future implementations, consider adding functionality to return a status
 *       indicating the success or failure of the delete operation.
 * 
 * @warning If the list is empty, the function will exit without changing the list state.
 * 
 * @return This function does not return a value.
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
 * @brief Deletes the element following the active element in the doubly linked list.
 * 
 * @details If the list has an active element and it is not the last element, this function
 *          removes the element immediately following the active element. If the list is inactive,
 *          or the active element is the last one, no action is taken.
 * 
 * @param list Pointer to the initialized structure of a doubly linked list.
 * 
 * @pre The list must be initialized and must have an active element that is not the last
 *      element for this operation to have an effect.
 * 
 * @post If conditions are met, the element after the active element is deleted, and the list's
 *       structure is updated to reflect this change. If the deleted element was the last one,
 *       the active element becomes the new last element of the list.
 * 
 * @note This function assumes that the list management functions such as DLL_IsActive are
 *       correctly implemented.
 * 
 * @code
 *   DLList myList;
 *   DLL_Init(&myList);
 *   DLL_InsertFirst(&myList, 10);
 *   DLL_InsertLast(&myList, 20);
 *   DLL_First(&myList);
 *   DLL_DeleteAfter(&myList); // Deletes the element after the first (20 in this case)
 * @endcode
 * 
 * @todo Future implementations could return a status code indicating the success or failure
 *       of the deletion operation.
 * 
 * @warning If the list is inactive or the active element is the last one, the function exits
 *          without performing any action.
 * 
 * @return This function does not return a value.
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
 * @brief Deletes the element before the active element in the doubly linked list.
 * 
 * @details If the list has an active element and it is not the first element, this function
 *          removes the element immediately preceding the active element. If the list is inactive,
 *          or the active element is the first one, no action is taken.
 * 
 * @param list Pointer to the initialized structure of a doubly linked list.
 * 
 * @pre The list must be initialized and must have an active element that is not the first
 *      element for this operation to have an effect.
 * 
 * @post If conditions are met, the element before the active element is deleted, and the list's
 *       structure is updated to reflect this change. If the deleted element was the first one,
 *       the active element becomes the new first element of the list.
 * 
 * @note This function assumes that the list management functions such as DLL_IsActive are
 *       correctly implemented.
 * 
 * @code
 *   DLList myList;
 *   DLL_Init(&myList);
 *   DLL_InsertFirst(&myList, 10);
 *   DLL_InsertFirst(&myList, 20);
 *   DLL_Last(&myList);
 *   DLL_DeleteBefore(&myList); // Deletes the element before the last (20 in this case)
 * @endcode
 * 
 * @todo Future implementations could return a status code indicating the success or failure
 *       of the deletion operation.
 * 
 * @warning If the list is inactive or the active element is the first one, the function exits
 *          without performing any action.
 * 
 * @return This function does not return a value.
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
 * @brief Inserts a new element after the active element in the doubly linked list.
 * 
 * @details If the list is active, this function creates a new element with the specified data 
 *          and inserts it immediately after the active element. If memory allocation fails,
 *          the DLL_Error() function is called to handle the error.
 * 
 * @param list Pointer to the initialized structure of a doubly linked list.
 * @param data Value to be inserted into the list after the currently active element.
 * 
 * @pre The list must be initialized and active; otherwise, the function will not insert a new element.
 * 
 * @post If the list was active, a new element is inserted after the active element, and the list
 *       structure is updated accordingly. If the active element was the last in the list, the new 
 *       element becomes the last element. If memory allocation fails, an error is reported.
 * 
 * @note The function is dependent on the DLL_IsActive function to check the activity of the list 
 *       and the DLL_Error function to handle memory allocation errors.
 * 
 * @code
 *   DLList myList;
 *   DLL_Init(&myList);
 *   DLL_InsertFirst(&myList, 10);
 *   DLL_First(&myList);
 *   DLL_InsertAfter(&myList, 20); // Inserts 20 after the first element (10)
 * @endcode
 * 
 * @todo Consider returning a status code to indicate the success of the operation or the nature 
 *       of any errors that occur.
 * 
 * @warning If the list is inactive, the function will exit without inserting a new element. If memory 
 *          allocation fails, the error handling function DLL_Error() is called, which may affect 
 *          the program's state or execution flow.
 * 
 * @return This function does not return a value.
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
 * @brief Inserts a new element before the active element in the doubly linked list.
 * 
 * @details If the list is active, this function creates a new element with the specified data 
 *          and inserts it immediately before the active element. If memory allocation fails,
 *          the DLL_Error() function is called to handle the error.
 * 
 * @param list Pointer to the initialized structure of a doubly linked list.
 * @param data Value to be inserted into the list before the currently active element.
 * 
 * @pre The list must be initialized and active for the insertion to proceed.
 * 
 * @post If the list was active, a new element is inserted before the active element, and the list
 *       structure is updated accordingly. If the active element was the first in the list, the new
 *       element becomes the first element. If memory allocation fails, an error is reported.
 * 
 * @note The function relies on DLL_IsActive to verify the list's activity and DLL_Error to 
 *       handle memory allocation errors.
 * 
 * @code
 *   DLList myList;
 *   DLL_Init(&myList);
 *   DLL_InsertFirst(&myList, 10);
 *   DLL_First(&myList);
 *   DLL_InsertBefore(&myList, 20); // Inserts 20 before the first element (10)
 * @endcode
 * 
 * @todo Consider implementing a return value to indicate the success of the insertion or the 
 *       nature of any errors that occur.
 * 
 * @warning If the list is inactive, the function will not perform the insertion. If memory
 *          allocation fails, DLL_Error() is called, which may change the program state or 
 *          execution flow.
 * 
 * @return This function does not return a value.
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
 * @brief Retrieves the value of the active element in the doubly linked list.
 * 
 * @details If the list is active, the value of the active element is passed through the 
 *          dataPtr parameter. If the list is not active, the DLL_Error() function is called.
 * 
 * @param list Pointer to the initialized structure of a doubly linked list.
 * @param dataPtr Pointer to the target variable where the active element's value will be stored.
 * 
 * @pre The list must be initialized and active for the retrieval to proceed. 'dataPtr' should
 *      point to a valid integer that can store the retrieved value.
 * 
 * @post If the list is active, the value of the active element is stored at the location 
 *       pointed to by dataPtr. If the list is inactive, DLL_Error() is called to report the error.
 * 
 * @note Assumes DLL_Error is properly implemented for error reporting.
 * 
 * @code
 *   DLList myList;
 *   DLL_Init(&myList);
 *   DLL_InsertFirst(&myList, 10);
 *   DLL_First(&myList);
 *   int value = DLL_GetValue(&myList); // Retrieves value of the active element (10)
 *   printf("Active element value: %d\n", value);
 * @endcode
 * 
 * @todo Consider returning a status code to indicate whether the retrieval was successful.
 * 
 * @warning If the list is not active, DLL_Error() will be invoked, and the value at dataPtr 
 *          will not be updated.
 * 
 * @return This function does not return a value.
 */
void DLL_GetValue(DLList *list, int *dataPtr) {

    if (list->activeElement == NULL) {
        DLL_Error();
    } else {
        *dataPtr = list->activeElement->data;
    }
}

/**
 * @brief Overwrites the value of the active element in the doubly linked list.
 * 
 * @details If the list is active, this function updates the data of the active element 
 *          with the new value provided. If the list is not active, no action is taken.
 * 
 * @param list Pointer to the initialized structure of a doubly linked list.
 * @param data New value to set for the currently active element.
 * 
 * @pre The list must be initialized and active for the update to occur.
 * 
 * @post If the list is active, the value of the active element is updated. If the list
 *       is not active, the state of the list remains unchanged.
 * 
 * @note This operation does not affect the structure or other elements of the list.
 * 
 * @code
 *   DLList myList;
 *   DLL_Init(&myList);
 *   DLL_InsertFirst(&myList, 10);
 *   DLL_First(&myList);
 *   DLL_SetValue(&myList, 20); // Sets the value of the active element to 20
 * @endcode
 * 
 * @todo Future enhancements may include returning a status indicator for the operation's
 *       success or failure.
 * 
 * @warning There is no action if the list is inactive, and no error is reported.
 * 
 * @return This function does not return a value.
 */
void DLL_SetValue(DLList *list, int data) {

    if (list->activeElement != NULL) {
        list->activeElement->data = data;
    }
}

/**
 * @brief Moves the activity to the next element in the doubly linked list.
 * 
 * @details If the list is active, the function advances the activity to the next element.
 *          If the active element was the last one, the list becomes inactive after the
 *          operation. If the list is not active, no action is taken.
 * 
 * @param list Pointer to the initialized structure of a doubly linked list.
 * 
 * @pre The list must be initialized before calling this function. If the list is inactive,
 *      the function will not change its state.
 * 
 * @post The activity is moved to the next element in the list. If the active element was
 *       the last element, the list becomes inactive.
 * 
 * @note This operation will only move the activity marker and does not modify the list's data
 *       or structure.
 * 
 * @code
 *   DLList myList;
 *   DLL_Init(&myList);
 *   DLL_InsertFirst(&myList, 10);
 *   DLL_InsertLast(&myList, 20);
 *   DLL_First(&myList);
 *   DLL_Next(&myList); // Moves activity to the second element (20)
 * @endcode
 * 
 * @todo Consider implementing functionality to return a status code indicating whether the
 *       activity was successfully moved or if the list became inactive.
 * 
 * @warning If the active element is the last one, calling this function will result in the
 *          list losing its active state.
 * 
 * @return This function does not return a value.
 */
void DLL_Next(DLList *list) {

    if (list->activeElement != NULL) {
        list->activeElement = list->activeElement->nextElement;
    }
}


/**
 * @brief Moves the activity to the previous element in the doubly linked list.
 * 
 * @details If the list is active, this function moves the activity to the preceding element.
 *          If the active element was the first one, the list becomes inactive after this
 *          operation. If the list is not active, the function will not perform any action.
 * 
 * @param list Pointer to the initialized structure of a doubly linked list.
 * 
 * @pre The list must be initialized before this function is invoked. If the list is inactive,
 *      the function will not modify its state.
 * 
 * @post If the list was active, the activity is moved to the previous element. If the active
 *       element was the first element, the list becomes inactive.
 * 
 * @note This function only updates the activity within the list and does not alter the data or
 *       the structure of the list itself.
 * 
 * @code
 *   DLList myList;
 *   DLL_Init(&myList);
 *   DLL_InsertFirst(&myList, 10);
 *   DLL_InsertLast(&myList, 20);
 *   DLL_Last(&myList);
 *   DLL_Previous(&myList); // Moves activity to the first element (10)
 * @endcode
 * 
 * @todo In future implementations, it may be useful to return a status indicating the result
 *       of the operation, such as whether the activity was successfully moved or if the list
 *       became inactive as a result.
 * 
 * @warning If the active element is the first one, invoking this function will result in the
 *          list becoming inactive.
 * 
 * @return This function does not return a value.
 */
void DLL_Previous(DLList *list) {

    if (list->activeElement != NULL) {
        list->activeElement = list->activeElement->previousElement;
    }
}

/**
 * @brief Checks if there is an active element in the doubly linked list.
 * 
 * @details This function returns a non-zero value if the list has an active element,
 *          indicating that there is a specific element ready for operations. If the list
 *          is inactive, it returns 0.
 * 
 * @param list Pointer to the initialized structure of a doubly linked list.
 * 
 * @pre The list must be initialized before calling this function.
 * 
 * @note This function is suitable for use in conditional statements to check the activity status
 *       of the list before performing operations that require an active element.
 * 
 * @code
 *   DLList myList;
 *   DLL_Init(&myList);
 *   DLL_InsertFirst(&myList, 10);
 *   DLL_First(&myList);
 *   if (DLL_IsActive(&myList)) {
 *       printf("An active element exists.\n");
 *   }
 * @endcode
 * 
 * @todo No further implementation is required unless additional functionality is to be added
 *       for activity status handling.
 * 
 * @warning There are no warnings associated with this function as it does not modify the list.
 * 
 * @retval 0 The list is inactive (no active element).
 * @retval non-zero The list has an active element.
 */
int DLL_IsActive(DLList *list) {

    return (list->activeElement != NULL);
}

/* End of c206.c */
