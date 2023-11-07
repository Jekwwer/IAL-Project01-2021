/**
 * @file c204.c
 * @brief Conversion of infix expression to postfix using stack.
 * @details This file contains the implementation for converting an infix notation
 *          of a mathematical expression to a postfix form, utilizing the stack
 *          data structure defined in c202. This task should be attempted only after
 *          successfully completing the c202 task, as it relies on the stack
 *          operations defined there.
 * 
 *          The primary function implemented in this file is:
 *          - infix2postfix: Converts an infix expression to postfix notation.
 * 
 *          Additionally, the following helper functions are implemented for better
 *          code clarity:
 *          - untilLeftPar: Empties the stack up to the left parenthesis.
 *          - doOperation: Processes the operator in the converted expression.
 * 
 * @note The implementation depends on the stack operations defined in c202.
 * 
 * @note This code file is designed for task-specific implementation and solving. 
 *       It is not meant to function as a standalone program. 
 *       However, it is modular and can be integrated into any larger program as needed.
 * 
 * @code
 * // Example usage:
 * char *postfix = infix2postfix("a+b*c");
 * printf("Postfix: %s\n", postfix);
 * @endcode
 * 
 * @see c202.h and c202.c for stack definitions and constants.
 * 
 * @see https://github.com/Jekwwer/IAL-Project01-2021 for the project repository.
 * 
 * @author Petr Přikryl (original concept), 
 *         Lukáš Maršík (C language conversion),
 *         Kamil Jeřábek (editor),
 *         Daniel Dolejška (editor)
 *         Evgenii Shiliaev (solution author)
 * @date November 1994 (original concept),
 *       December 2012 (C language conversion),
 *       September 2019 (edit),
 *       October 2021 (solution)
 *       November 2023 (code comments updated)
 */

#include "c204.h"
#include <string.h>

int solved;


/**
 * @brief Empties the stack up to the left parenthesis and appends operators to postfix expression.
 * 
 * @details This helper function is used during the conversion of an infix expression to
 *          postfix notation. It removes all characters from the stack until it encounters
 *          a left parenthesis '(', appending each operator to the postfix expression. The
 *          left parenthesis is also removed but not added to the postfix expression.
 *          If the stack is empty before reaching a left parenthesis, the function terminates.
 * 
 * @param stack Pointer to the initialized stack structure.
 * @param postfixExpression Character string containing the resulting postfix expression.
 * @param postfixExpressionLength Pointer to the current length of the resulting postfix expression.
 * 
 * @pre The stack must be initialized and contain at least one left parenthesis '('. The
 *      postfixExpressionLength must correctly reflect the current length of the postfix
 *      expression.
 * 
 * @post The characters up to and including the first left parenthesis are removed from the
 *       stack. The postfixExpression is extended with the operators removed from the stack.
 *       The postfixExpressionLength is updated to reflect the new length of the expression.
 * 
 * @note A helper variable of type char is declared and used to minimize the number of
 *       accesses to the stack structure.
 * 
 * @warning If the stack does not contain a left parenthesis '(', the function will empty
 *          the stack completely, which may not be the intended behavior.
 * 
 * @return This function does not return a value.
 * 
 * @todo Consider implementing error handling to address situations where the stack does not
 *       contain a left parenthesis '('.
 */
void untilLeftPar(Stack *stack, char *postfixExpression,
                  unsigned *postfixExpressionLength) {

    char c = '\0';
    // Until we get the left parenthesis from the top of the stack
    while (Stack_Top(stack, &c), c != '(') {
        // Add elements from the stack to the result
        postfixExpression[*postfixExpressionLength] = c;
        (*postfixExpressionLength)++;
        Stack_Pop(stack);
    };
    Stack_Pop(stack);
}

/**
 * @brief Processes an operator and decides its placement in postfix expression.
 * 
 * @details When an operator is read from the input, this function manages it according to
 *          its precedence relative to the operator at the top of the stack. Operators with
 *          higher precedence are pushed onto the stack, while those with lower or equal
 *          precedence are popped from the stack and added to the postfix expression until
 *          the correct position for the new operator is found.
 * 
 * @param stack Pointer to the initialized stack structure.
 * @param c The current operator character that is being processed.
 * @param postfixExpression Character string containing the resulting postfix expression.
 * @param postfixExpressionLength Pointer to the current length of the resulting postfix expression.
 * 
 * @pre The stack must be initialized before calling this function. The input character, 'c',
 *      is expected to be a valid operator. The postfixExpression and postfixExpressionLength
 *      should be correctly initialized to store the resulting postfix expression.
 * 
 * @post The stack may have new operators pushed onto it, or existing operators popped off
 *       depending on the precedence. The postfixExpression is modified to include operators
 *       in their postfix order, and postfixExpressionLength is updated accordingly.
 * 
 * @note The function uses recursion to handle operators with lower or equal precedence.
 * 
 * @warning The function assumes that the operator 'c' and the operators in the stack are
 *          from the set { '+', '-', '*', '/' }. Undefined behavior may occur if other
 *          characters are used.
 * 
 * @return This function does not return a value.
 * 
 * @todo Implement a more robust error checking for invalid operators and handle cases where
 *       the stack becomes full during operation processing.
 */
void doOperation(Stack *stack, char c, char *postfixExpression,
                 unsigned *postfixExpressionLength) {

    char top;

    // If the stack is empty
    if (Stack_IsEmpty(stack) ||
        // Or there's a left parenthesis at the top
        (Stack_Top(stack, &top), top == '(') ||
        // Or there's an operator with lower priority at the top
        (strchr("+-", top) != NULL && strchr("/*", c) != NULL)) {

        Stack_Push(stack, c);
        // Otherwise insert the top of the stack into the resulting string and call the function again
    } else {
        postfixExpression[*postfixExpressionLength] = top;
        (*postfixExpressionLength)++;
        Stack_Pop(stack);
        doOperation(stack, c, postfixExpression, postfixExpressionLength);
    }
}

/**
 * @brief Converts an infix expression to postfix notation.
 * 
 * @details This function takes an infix expression as input and produces the corresponding
 *          postfix expression. It uses a stack to manage operators and respects the
 *          mathematical precedence of operations. Memory is dynamically allocated for
 *          the output string, which must be freed by the calling function.
 * 
 * @param infixExpression Character string containing the infix expression to convert.
 * 
 * @pre The input string should be a valid infix expression formatted according to the
 *      specifications and terminated with an '=' character. The expression should not
 *      exceed MAX_LEN - 1 characters.
 * 
 * @post The returned string will contain the postfix expression equivalent of the
 *       provided infix expression. The stack used for conversion is properly freed
 *       before exiting the function.
 * 
 * @note The function assumes the input is well-formed and does not perform validation.
 *       It uses helper functions untilLeftPar and doOperation for processing.
 * 
 * @warning In case of memory allocation failure, the function returns NULL.
 * 
 * @retval char* A dynamically allocated string containing the resulting postfix expression.
 *               It is the caller's responsibility to free this memory.
 * 
 * @todo Implement input validation to gracefully handle malformed expressions and
 *       enhance error handling for memory allocation issues.
 * 
 * @returns Character string containing the resulting postfix expression.
 */
char *infix2postfix(const char *infixExpression) {

    Stack *stack = (Stack *) malloc(sizeof(Stack));
    Stack_Init(stack);

    // Allocate as much memory as the input string takes
    char *result = (char *) malloc(sizeof(char) * MAX_LEN);
    if (result == NULL) {
        return NULL;
    }

    unsigned int i = 0;// For traversing the input
    unsigned int j = 0;// For writing to the output

    // Processing operands
    while (infixExpression[i] != '\0') {
        if ((infixExpression[i] >= 'a' && infixExpression[i] <= 'z') ||
            (infixExpression[i] >= 'A' && infixExpression[i] <= 'Z') ||
            (infixExpression[i] >= '0' && infixExpression[i] <= '9')) {

            result[j] = infixExpression[i];
            j++;
        }

        // Processing brackets
        if (infixExpression[i] == '(') {
            Stack_Push(stack, infixExpression[i]);
        }

        if (infixExpression[i] == ')') {
            untilLeftPar(stack, result, &j);
        }

        // Processing operators
        if (strchr("+-/*", infixExpression[i]) != NULL) {
            doOperation(stack, infixExpression[i], result, &j);
        }

        // Processing delimiter (equals sign)
        if (infixExpression[i] == '=') {
            while (!Stack_IsEmpty(stack)) {
                char c;
                Stack_Top(stack, &c);
                Stack_Pop(stack);
                result[j] = c;
                j++;
            }
            result[j] = '=';
            j++;
            result[j] = '\0';
            break;
        }
        i++;
    }

    // Releasing the allocated stack
    while (!Stack_IsEmpty(stack)) {
        Stack_Pop(stack);
    }
    free(stack);

    return result;
}

/* End of c204.c */
