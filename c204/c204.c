
/* ******************************* c204.c *********************************** */
/*  Course: Algorithms (IAL) - FIT VUT in Brno                               */
/*  Task: c204 - Conversion of infix expression to postfix (using c202)       */
/*  Reference implementation: Petr Přikryl, November 1994                     */
/*  Conversion to the C language: Lukáš Maršík, December 2012                 */
/*  Edited by: Kamil Jeřábek, September 2019                                  */
/*            Daniel Dolejška, September 2021                                */
/* ************************************************************************** */
/*
** Implement the procedure for converting an infix notation of a mathematical expression
** to a postfix form. For the conversion, use a stack (Stack) that was
** implemented within the example c202. Do not attempt to solve this example
** without correctly solving the example c202 first.
**
** Implement the following function:
**
**    infix2postfix ... conversion function to transform infix expression
**                      to postfix
**
** For better code clarity, implement the following helper functions:
**
**    untilLeftPar ... empty the stack until the left parenthesis
**    doOperation .... process the operator of the converted expression
**
** Comment your solution purposefully.
**
** Terminological note: The C language does not use the term procedure.
** Hence, we use the term function here for operations that would be
** implemented as procedures in an algorithmic language of the Pascal type.
** (In the C language, procedures correspond to functions returning the type void).
**
**/

#include "c204.h"
#include <string.h>

int solved;


/**
 * Helper function untilLeftPar.
 * It serves to empty the stack until the left parenthesis, with the left parenthesis
 * also being removed.
 * If the stack is empty, the function's execution ends.
 *
 * Insert the operators removed from the stack into the output character array
 * postfixExpression in sequence.
 * The length of the converted expression, and also the pointer to the first available spot
 * for writing, is represented by the parameter postfixExpressionLength.
 *
 * To minimize the number of accesses to the stack structure, you can
 * declare and use a helper variable of type char here.
 *
 * @param stack Pointer to the initialized stack structure
 * @param postfixExpression Character string containing the resulting postfix expression
 * @param postfixExpressionLength Pointer to the current length of the resulting
 * postfix expression
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
 * Helper function doOperation.
 * Processes the operator passed by parameter c after reading the character from
 * the input character array.
 *
 * Based on the priority of the passed operator and possibly the priority of the operator at the top
 * of the stack, we decide on the next steps.
 * The length of the converted expression and also the pointer to the first free space, into which
 * we should write, is represented by the parameter postfixExpressionLength. The output
 * character array is again postfixExpression.
 *
 * @param stack Pointer to the initialized stack structure
 * @param c Character of the operator in the expression
 * @param postfixExpression Character string containing the resulting postfix expression
 * @param postfixExpressionLength Pointer to the current length of the resulting 
 * postfix expression
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
 * Conversion function infix2postfix.
 * Reads an infix expression from the input string infixExpression and generates
 * the corresponding postfix expression to the output string (find the conversion procedure
 * in the lectures or study materials).
 * Memory for the output string (of size MAX_LEN) needs to be allocated. The calling
 * function, i.e., the receiver of the converted string, ensures the proper release of the 
 * memory allocated here.
 *
 * Expression format:
 * 1. The expression contains operators + - * / in the meaning of addition, subtraction,
 *    multiplication, and division. Addition has the same priority as subtraction,
 *    multiplication has the same priority as division. The priority of multiplication is
 *    higher than the priority of addition. All operators are binary
 *    (unary minus is not considered).
 *
 * 2. Values in the expression are represented by single-character identifiers
 *    and numbers - 0..9, a..z, A..Z (case-sensitive).
 *
 * 3. The expression can use an unspecified number of pairs of round
 *    brackets. Assume that the input expression is written correctly (do not handle
 *    incorrect expression input).
 *
 * 4. Every correctly written expression (both infix and postfix) must be terminated
 *    with the '=' character.
 *
 * 5. With the same operator priority, the expression is evaluated from left to right.
 *
 * Implementation notes
 * --------------------
 * Use the character stack Stack implemented in the example c202.
 * For stack operations, use exclusively operations from its interface.
 *
 * When implementing, make use of the helper functions untilLeftPar and doOperation.
 *
 * The string (of infix and postfix expression) means a char array,
 * which is correctly terminated with a null character according to C language conventions.
 *
 * Expect only correctly written and terminated expressions as input. Their length
 * won't exceed MAX_LEN-1 (MAX_LEN including the null character) so even the resulting expression
 * should fit into the allocated array. Always verify that memory allocation was successful 
 * after dynamic memory allocation. In case of allocation error, return NULL instead of the string.
 *
 * @param infixExpression Character string containing the infix expression to convert
 *
 * @returns Character string containing the resulting postfix expression
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
