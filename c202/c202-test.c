/* **************************** c202-test.c ********************************* */
/*  Course: Algorithms (IAL) - FIT VUT in Brno                                */
/*  Task: c202 - Stack of characters in an array                               */
/*  Created by: Václav Topinka, September 2005                                 */
/*  Modified by: Kamil Jeřábek, September 2019                                 */
/*              Daniel Dolejška, September 2021                                */
/* ************************************************************************** */

/* Basic tests for c202.c */

#include "c202.h"

#include <stdio.h>
#include <stdlib.h>

Stack *stack;
int STACK_SIZE;
int error_flag;
int solved;

/****************************************************************************** 
 * Special handling of the tested functions.                                  *
 ******************************************************************************/

/** Prints the content of the stack. */
void stackPrint( Stack *stack ) {
	if (solved)
	{
		int maxi = stack->topIndex;
		if (stack->topIndex > STACK_SIZE - 1)
		{
			printf("Warning: stack->topIndex (value: %i) is out of range STACK_SIZE (%i).\n", stack->topIndex,
			       STACK_SIZE);
			maxi = STACK_SIZE - 1;
		}
		printf("--- BOTTOM [ ");
		for (int i = 0; i <= maxi; i++)
			putchar(stack->array[i]);
		printf(" ] TOP ---\n");
	}
}

/** Calls the Stack_Init function and if it's not implemented, reports it. */
void use_stack_init( Stack *stack ) {
	solved = TRUE;
	Stack_Init(stack);
	if (!solved)
		printf("[W] Function Stack_Init was not implemented.\n");
}

/** Calls the Stack_IsEmpty function and prints the result. */
void use_stack_empty( Stack *stack ) {
	solved = TRUE;
	int i = Stack_IsEmpty(stack);
	if (!solved)
		printf("[W] Function Stack_IsEmpty was not implemented.\n");
	else
		printf("Stack_IsEmpty returned '%s'\n", i ? "TRUE" : "FALSE");
}

/** Calls the Stack_IsFull function and prints the result. */
void use_stack_full( Stack *stack ) {
	solved = TRUE;
	int i = Stack_IsFull(stack);
	if (!solved)
		printf("[W] Function Stack_IsFull was not implemented.\n");
	else
		printf("Stack_IsFull returned '%s'\n", i ? "TRUE" : "FALSE");
}

/** Calls the Stack_Top function and prints the result. */
void use_stack_top( Stack *stack ) {
	solved = TRUE;
	error_flag = 0;
	char c;
	Stack_Top(stack, &c);
	if (!solved)
		printf("[W] Function Stack_Top was not implemented.\n");
	else if (!error_flag)
		printf("Stack_Top returned '%c'\n", c);
}

/** Calls the Stack_Pop function. */
void use_stack_pop( Stack *stack ) {
	solved = TRUE;
	Stack_Pop(stack);
	if (!solved)
		printf("[W] Function Stack_Pop was not implemented.\n");
}

/** Calls the Stack_Push function. */
void use_stack_push( Stack *stack, char c ) {
	solved = TRUE;
	Stack_Push(stack, c);
	if (!solved)
		printf("[W] Function Stack_Push was not implemented.\n");
}

/****************************************************************************** 
 * Actual testing                                                             *
 ******************************************************************************/

int main() {
	printf("C202 - Stack Implemented Using an Array - Basic Tests\n");
	printf("-----------------------------------------------------\n");

	STACK_SIZE = 8;
	stack = (Stack *) malloc(sizeof(Stack));

	printf("\n[TEST01] Stack initialization\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	use_stack_init(stack);
	stackPrint(stack);

	printf("\n[TEST02] Checking a state of the stack\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	use_stack_empty(stack);
	use_stack_full(stack);

	printf("\n[TEST03] Pushing a first item 'A'\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	use_stack_push(stack, 'A');
	stackPrint(stack);

	printf("\n[TEST04] Checking a state of the stack again\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	use_stack_empty(stack);
	use_stack_full(stack);

	printf("\n[TEST05] Reading and removing the top item\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	use_stack_top(stack);
	use_stack_pop(stack);
	stackPrint(stack);

	printf("\n[TEST06] Pushing items from '0' to '7'\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	for (int i = 0; i < 8; i++)
		use_stack_push(stack, '0' + i);
	stackPrint(stack);

	printf("\n[TEST07] Checking a state of the stack\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	use_stack_empty(stack);
	use_stack_full(stack);

	printf("\n[TEST08] Removing all items one by one\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	for (int i = 0; i < 8; i++)
	{
		use_stack_top(stack);
		use_stack_pop(stack);
	}
	stackPrint(stack);

	printf("\n[TEST09] Final check of the stack\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	use_stack_empty(stack);
	use_stack_full(stack);

	printf("\n\n----- C202 - The End of Basic Tests -----\n");

	free(stack);
	return (0);
}

/* End of c202-test.c */
