/* ******************************* c202.h *********************************** */
/*  Course: Algorithms (IAL) - FIT VUT in Brno                               */
/*  Task: c202 - Character stack in an array                                  */
/*  Header file for c202.c                                                    */
/*  Created by: Václav Topinka, September 2005                                */
/*  Modifications: Kamil Jeřábek, September 2019                              */
/*                 Daniel Dolejška, September 2021                            */
/* ************************************************************************** */

/* PLEASE DO NOT MODIFY THIS FILE! */

#ifndef _STACK_H_
#define _STACK_H_

#include <stdio.h>

#define TRUE 1
#define FALSE 0

/**
 * The MAX_STACK value specifies the actual size of the static array for storing
 * stack values.
 * When implementing, do not use the MAX_STACK value at all.
 */
#define MAX_STACK 20

/**
 * When implementing operations on the ADT stack, assume that the size of this
 * array is only STACK_SIZE.
 * This will make it easy to change the size of the stack during testing.
 */
extern int STACK_SIZE;

/** Global variable - indicates if an error was called during the operation. */
extern int error_flag;
/** Global variable - indicates if the operation was solved. */
extern int solved;

/** Total number of possible errors. */
#define MAX_SERR    3
/** Error during Stack_Init. */
#define SERR_INIT   1
/** Error during Stack_Push. */
#define SERR_PUSH   2
/** Error during Stack_Top. */
#define SERR_TOP    3

/** ADT stack implemented in a static array. */
typedef struct {
	/** Array for storing values. */
	char array[MAX_STACK];
	/** Index of the top element on the stack. */
	int topIndex;
} Stack;

void Stack_Error( int );

void Stack_Init( Stack * );

int Stack_IsEmpty( const Stack * );

int Stack_IsFull( const Stack * );

void Stack_Top( const Stack *, char * );

void Stack_Pop( Stack * );

void Stack_Push( Stack *, char );

#endif

/* End of header file c202.h */
