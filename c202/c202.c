
/**
 * @file c202.c
 * @brief Stack of characters in an array implementation file.
 * @details This file is a reference implementation of a character stack data type
 *          using a static array. It includes essential stack operations and their
 *          implementation as functions. The ADT stack is represented by a structure
 *          defined in the header file c202.h, which includes a static 'array' and
 *          'topIndex' to manage the stack elements.
 * 
 *          The functions implemented are:
 *          - Stack_Init:    Initializes the stack.
 *          - Stack_IsEmpty: Checks if the stack is empty.
 *          - Stack_IsFull:  Checks if the stack is full.
 *          - Stack_Top:     Reads the value from the top of the stack without removing it.
 *          - Stack_Pop:     Removes an item from the top of the stack.
 *          - Stack_Push:    Adds an item to the top of the stack.
 *
 *          For a detailed type definition and functions usage, see c202.h header file.
 *          Purposeful comments are included with each function implementation for clarity.
 *
 * @note This code file is designed for task-specific implementation and solving. 
 *       It is not meant to function as a standalone program. 
 *       However, it is modular and can be integrated into any larger program as needed.
 * 
 * @code
 * // Using example
 * Stack s;
 * Stack_Init(&s);
 * if (!Stack_IsFull(&s)) {
 *     Stack_Push(&s, 'a');
 * }
 * if (!Stack_IsEmpty(&s)) {
 *     char topElement;
 *     Stack_Top(&s, &topElement);
 *     Stack_Pop(&s);
 * }
 * @endcode
 *
 * @see c202.h for type definitions and constants.
 * 
 * @see https://github.com/Jekwwer/IAL-Project01-2021 for the project repository.
 * 
 * @author Petr Přikryl (original author),
 *         Václav Topinka (creator), 
 *         Kamil Jeřábek (revisor), 
 *         Daniel Dolejška (revisor), 
 *         Evgenii Shiliaev (solution author)
 * 
 * @date 1994 (original concept),
 *       September 2005 (creation),
 *       September 2019 (revisions),
 *       October 2021 (solution)
 *       November 2023 (code comments updated)
 */

#include "c202.h"

int STACK_SIZE = MAX_STACK;
int error_flag;
int solved;

/**
 * @brief Reports an error encountered during stack operations.
 * 
 * @details This function is responsible for handling errors that occur while working
 *          with the stack. It prints a warning message to the standard output that
 *          corresponds to an internal error identifier. The error messages are defined
 *          within a static array and cover a range of errors that include initialization,
 *          push, and top operation errors. If an invalid error code is provided, it
 *          defaults to "Unknown error".
 * 
 * @param error_code The internal error identifier corresponding to the encountered error.
 * 
 * @pre The error_code must be a defined error identifier within the range of known error
 *      codes, otherwise, the default "Unknown error" message is used.
 * 
 * @post Upon execution, an error message is printed to the standard output, and an
 *       internal error flag is set to 1 to indicate that an error has occurred.
 * 
 * @note This function should not be modified as it is part of the core error handling
 *       mechanism for the stack operations. Modification could lead to undefined behavior
 *       in the error reporting process.
 * 
 * @code
 * if (Stack_IsFull(&s)) {
 *     Stack_Error(SERR_PUSH);
 * }
 * @endcode
 * 
 * @warning The function relies on the error codes being correctly defined and within the
 *          valid range. Passing an error code outside of the valid range results in an
 *          "Unknown error" message.
 * 
 * @return This function does not return a value.
 * 
 * @todo Consider enhancing the error handling process by implementing additional error
 *       reporting mechanisms, such as logging to a file or integrating with a debugging
 *       tool for more comprehensive diagnostics.
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
 * @brief Initializes the stack to its default empty state.
 * 
 * @details Sets the topIndex of the stack to -1 to indicate that the stack is empty.
 *          This function must be called before any operations are performed on the
 *          stack. The contents of the static array representing the stack are not
 *          modified and thus remain undefined until explicitly set.
 * 
 * @param stack Pointer to the stack structure to be initialized.
 * 
 * @pre The stack pointer provided must not be NULL. If a NULL pointer is passed, the
 *      Stack_Error function is called with SERR_INIT to handle the error.
 * 
 * @post After execution, the stack is in a defined state with topIndex set to -1.
 *       The stack is ready for operations like push and pop.
 * 
 * @note This function assumes that the stack is not already initialized. If it is
 *       already initialized, this function will reinitialize it.
 * 
 * @code
 * Stack myStack;
 * Stack_Init(&myStack); // Proper initialization of the stack before usage.
 * @endcode
 * 
 * @warning If 'stack' is NULL, an error is reported, and the function exits without
 *          performing any initialization. For simplicity, other functions will assume
 *          that this situation (stack == NULL) does not occur.
 * 
 * @return This function does not return a value.
 * 
 * @todo Ensure that the error handling mechanism is robust and communicates issues
 *       effectively to the user.
 */
void Stack_Init(Stack *stack) {

    if (stack == NULL) {
        Stack_Error(SERR_INIT);
    } else {
        stack->topIndex = -1;
    }
}

/**
 * @brief Determines if the stack is empty.
 * 
 * @details Checks the stack's top index to ascertain if there are no elements. An empty
 *          stack is indicated by the top index being set to -1. The function is designed
 *          to return the result in a single statement without conditional branching.
 * 
 * @param stack Pointer to the initialized stack structure to be checked.
 * 
 * @pre The stack must be initialized before calling this function. The stack structure
 *      should be in a valid state with the top index correctly reflecting the number
 *      of elements.
 * 
 * @post There is no change to the stack as a result of calling this function. It is a
 *       read-only operation that checks the stack's state.
 * 
 * @note This function uses a direct comparison rather than conditional statements to
 *       improve efficiency and reduce the risk of errors.
 * 
 * @code
 * if (Stack_IsEmpty(&s)) {
 *     // The stack is empty
 * }
 * @endcode
 * 
 * @warning Incorrect stack initialization could lead to false results. Ensure that the
 *          stack is properly initialized so that the top index reflects the actual
 *          stack contents.
 * 
 * @retval int Returns a non-zero value if the stack is empty, otherwise returns zero.
 * 
 * @todo If the stack's definition changes, ensure to update the empty condition check
 *       to maintain accuracy.
 */
int Stack_IsEmpty(const Stack *stack) {

    return stack->topIndex == -1;
}

/**
 * @brief Checks if the stack is full.
 * 
 * @details Determines whether the stack has reached its maximum capacity. The stack is
 *          considered full if the top index is equal to STACK_SIZE - 1. This function
 *          is implemented in a single command to avoid off-by-one errors.
 * 
 * @param stack Pointer to the initialized stack structure to check for fullness.
 * 
 * @pre The stack must be initialized before invoking this function. The stack is
 *      implemented using a zero-based index array, and STACK_SIZE is the maximum
 *      number of elements that can be stored.
 * 
 * @post No changes are made to the stack by this function. It only reads the state of
 *       the stack's top index to determine if it is full.
 * 
 * @note Be mindful of the zero-based indexing used in the underlying array when
 *       determining the stack's capacity.
 * 
 * @code
 * if (Stack_IsFull(&s)) {
 *     // The stack is full
 * }
 * @endcode
 * 
 * @warning The function assumes that the 'stack' pointer is valid and that the stack
 *          has been properly initialized. Passing a NULL pointer or an uninitialized
 *          stack could lead to undefined behavior.
 * 
 * @retval int Returns a non-zero value if the stack is full, otherwise returns zero.
 * 
 * @todo In future implementations, consider defining the return value as a boolean
 *       for clarity in the calling code.
 */
int Stack_IsFull(const Stack *stack) {

    return stack->topIndex == STACK_SIZE - 1;
}

/**
 * @brief Retrieves the top character from the stack without removal.
 * 
 * @details Accesses the character at the top of the stack and provides it via
 *          dataPtr. This operation does not modify the stack structure. An attempt
 *          to perform this operation on an empty stack is an incorrect use and is
 *          handled by calling Stack_Error with SERR_TOP.
 * 
 * @param stack Pointer to the initialized stack structure to be queried.
 * @param dataPtr Pointer to the destination variable where the top character will be stored.
 * 
 * @pre The stack must be initialized and not empty. Use Stack_IsEmpty to verify
 *      that there are items in the stack before calling this function. The dataPtr
 *      argument must point to a valid memory location where the character can be stored.
 * 
 * @post The state of the stack remains unchanged after this operation. The character at
 *       the top of the stack is copied to the location pointed to by dataPtr.
 * 
 * @note This function will not provide a meaningful value at dataPtr if the stack is
 *       empty. The error is handled internally and does not affect the caller's state.
 * 
 * @code
 * char topElement;
 * if (!Stack_IsEmpty(&s)) {
 *     Stack_Top(&s, &topElement); // Retrieve the top element
 *     // Use topElement as needed
 * }
 * @endcode
 * 
 * @warning The function triggers an error handling routine if it is called on an empty
 *          stack. It is the caller's responsibility to ensure the stack is not empty.
 * 
 * @return This function does not return a value.
 * 
 * @todo Consider modifying the function to return a status code that could be used by
 *       the caller to confirm whether the top character was successfully retrieved,
 *       especially in cases where the stack might be empty.
 */
void Stack_Top(const Stack *stack, char *dataPtr) {

    if (Stack_IsEmpty(stack)) {
        Stack_Error(SERR_TOP);
    }

    *dataPtr = stack->array[stack->topIndex];
}

/**
 * @brief Removes the top item from the stack.
 * 
 * @details This function decrements the top index of the stack, effectively removing
 *          the top element. The function does not return the removed element; it simply
 *          discards it. If the stack is empty before this operation, no changes are made.
 * 
 * @param stack A pointer to the stack structure from which the top item will be removed.
 * 
 * @pre The stack should be initialized before this function is called. It is the caller's
 *      responsibility to check if the stack is not empty using Stack_IsEmpty function
 *      to avoid underflow.
 * 
 * @post If the stack was not empty, the topIndex is decremented, reducing the size of
 *       the stack by one. If the stack was empty, the state of the stack remains unchanged.
 * 
 * @note For the cases where the stack is empty, this function silently fails without
 *       altering the stack or reporting an error. This is by design to simplify the
 *       error handling in the calling code.
 * 
 * @code
 * if (!Stack_IsEmpty(&s)) {
 *     Stack_Pop(&s); // Remove the top item
 * }
 * @endcode
 * 
 * @warning While this function does not report an error when called on an empty stack,
 *          doing so might indicate a logic error in the calling code. Users must ensure
 *          that the stack is not empty before calling this function to avoid unintended
 *          behavior.
 * 
 * @return This function does not return a value.
 * 
 * @todo Consider implementing a return value or error handling to inform the caller
 *       about the success of the pop operation, especially in cases where the stack
 *       is empty.
 */
void Stack_Pop(Stack *stack) {

    if (Stack_IsEmpty(stack)) {
        return;
    }

    stack->topIndex--;
}

/**
 * @brief Inserts a character on top of the stack.
 * 
 * @details This function adds a new character to the top of the stack. If the stack
 *          is already full before this operation, a stack error is reported by calling
 *          Stack_Error with the SERR_PUSH error code.
 * 
 * @param stack A pointer to the stack structure where the character will be inserted.
 * @param data The character to insert onto the stack.
 * 
 * @pre The stack should be initialized and not full before this function is called.
 *      The caller must ensure this by using Stack_IsFull function.
 * 
 * @post If the operation is successful, the topIndex is incremented and the new character
 *       is placed at the top of the stack. If the stack was full, the function reports
 *       an error and the state of the stack is not changed.
 * 
 * @note This function assumes that the stack is correctly initialized and that the
 *       'data' parameter contains a valid character.
 * 
 * @code
 * if (!Stack_IsFull(&s)) {
 *     Stack_Push(&s, 'a'); // Push 'a' on the stack
 * }
 * @endcode
 * 
 * @warning Calling this function with a full stack is considered an error. The function
 *          will not add the character to the stack, and it will trigger an error
 *          handling routine.
 * 
 * @return This function does not return a value.
 * 
 * @todo Consider returning a status code indicating the result of the operation, which
 *       could be used for more robust error handling and control flow in the calling code.
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
