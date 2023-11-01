
/* ******************************* c202.c *********************************** */
/*  Course: Algorithms (IAL) - FIT VUT in Brno                                */
/*  Assignment: c202 - Stack of characters in an array                         */
/*  Reference implementation: Petr Přikryl, 1994                               */
/*  Created by: Václav Topinka, September 2005                                */
/*  Revisions: Kamil Jeřábek, September 2019                                  */
/*             Daniel Dolejška, September 2021                                */
/* ************************************************************************** */
/*
** Implement a character stack data type in a static array. The ADT stack is
** represented by a record of type Stack. The static 'array' is indexed
** up to the maximum value of STACK_SIZE. The 'topIndex' record item points to the item
** on top of the stack. An empty stack corresponds to topIndex == -1,
** a stack with one item has a value of 0, etc. The exact definition of types can be found
** in the header file c202.h.
**
** Implement the following functions:
**
**    Stack_Init .... stack initialization
**    Stack_IsEmpty . test for stack emptiness
**    Stack_IsFull .. test for stack fullness
**    Stack_Top ..... reads the value from the top of the stack
**    Stack_Pop ..... removes an item from the top of the stack
**    Stack_Push .... inserts an item into the stack
**
** Please comment on your solution purposefully!
**
** Terminological note: The C language does not use the term procedure.
** Therefore, here we use the term function even for operations that would be
** implemented as procedures in an algorithmic language of the Pascal type
** (in C, procedures correspond to functions returning the void type).
**
**/

#include "c202.h"

int STACK_SIZE = MAX_STACK;
int error_flag;
int solved;

/**
 * Prints a warning that an error occurred while working with the stack.
 *
 * PLEASE DO NOT MODIFY THIS FUNCTION!
 *
 * @param error_code Internal error identifier
 */
void Stack_Error(int error_code) {
    static const char *SERR_STRINGS[MAX_SERR + 1] = {
            "Unknown error", "Stack error: INIT", "Stack error: PUSH",
            "Stack error: TOP"};

    if (error_code <= 0 || error_code > MAX_SERR)
        error_code = 0;
    printf("%s\n", SERR_STRINGS[error_code]);
    error_flag = 1;
}

/**
 * Initializes the stack - sets the top of the stack.
 * Do not modify the values in the static array - after initializing the stack
 * they are undefined.
 *
 * If the function receives stack == NULL as a parameter,
 * call the function Stack_Error(SERR_INIT).
 * For other functions, for simplification, assume that this situation
 * will not occur.
 *
 * @param stack Pointer to the stack structure
 */
void Stack_Init(Stack *stack) {

    if (stack == NULL) {
        Stack_Error(SERR_INIT);
    } else {
        stack->topIndex = -1;
    }
}

/**
 * Returns a non-zero value if the stack is empty, otherwise returns 0.
 * Implement the function in a single command.
 * Avoid constructs like "if (cond) b=true else b=false".
 *
 * @param stack Pointer to the initialized stack structure
 *
 * @returns Non-zero value if the stack is empty, otherwise zero
 */
int Stack_IsEmpty(const Stack *stack) {

    return stack->topIndex == -1;
}

/**
 * Returns a non-zero value if the stack is full, otherwise returns 0.
 * Be careful of the common "off-by-one" programming error here and think well
 * about when the stack is considered full, given that it can contain at most 
 * STACK_SIZE items and the first item is placed at position 0.
 *
 * Implement the function in a single command.
 *
 * @param stack Pointer to the initialized stack structure
 *
 * @returns Non-zero value if the stack is full, otherwise zero
 */
int Stack_IsFull(const Stack *stack) {

    return stack->topIndex == STACK_SIZE - 1;
}

/**
 * Returns the character from the top of the stack via the dataPtr parameter.
 * However, this operation does not remove the top item from the stack.
 * Calling the Top operation on an empty stack is incorrect and should be handled
 * by calling the Stack_Error(SERR_TOP) function.
 *
 * To check if the stack is empty, use the previously defined function 
 * Stack_IsEmpty.
 *
 * @param stack Pointer to the initialized stack structure
 * @param dataPtr Pointer to the destination variable
 */
void Stack_Top(const Stack *stack, char *dataPtr) {

    if (Stack_IsEmpty(stack)) {
        Stack_Error(SERR_TOP);
    }

    *dataPtr = stack->array[stack->topIndex];
}

/**
 * Removes an item from the top of the stack. To check if the stack is empty, 
 * use the previously defined Stack_IsEmpty function.
 *
 * Calling the Pop operation on an empty stack might indicate an error in the algorithm
 * where the stack is used, but do not call the error-handling function here 
 * (we can leave the stack empty). A warning might be more appropriate than 
 * an error call here, but for simplicity, we won't use one.
 *
 * @param stack Pointer to the initialized stack structure
 */
void Stack_Pop(Stack *stack) {

    if (Stack_IsEmpty(stack)) {
        return;
    }

    stack->topIndex--;
}

/**
 * Inserts a character onto the top of the stack. Attempting to insert an item into 
 * a full stack is incorrect and should be handled by calling the 
 * Stack_Error(SERR_PUSH) function.
 *
 * To check if the stack is full, use the previously defined Stack_IsFull function.
 *
 * @param stack Pointer to the initialized stack structure
 * @param data Character to insert
 */
void Stack_Push(Stack *stack, char data) {

    if (Stack_IsFull(stack)) {
        Stack_Error(SERR_PUSH);
    } else {
        stack->array[stack->topIndex + 1] = data;
        stack->topIndex++;
    }
}

/* End of c202.c */
