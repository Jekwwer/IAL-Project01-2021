/* ******************************* c206.h *********************************** */
/*  Course: Algorithms (IAL) - FIT VUT in Brno                                */
/*  Task: c206 - Doubly Linked Linear List                                    */
/*  Created by: Martin Tuček, September 2005                                  */
/*  Modified by: Kamil Jeřábek, September 2020                                */
/*              Daniel Dolejška, September 2021                               */
/* ************************************************************************** */

/* PLEASE DO NOT MODIFY THIS FILE! */

#include<stdio.h>
#include<stdlib.h>

#define FALSE 0
#define TRUE 1

/** Global variable - error handling flag. */
extern int error_flag;
/** Global variable - indicates if the operation was solved. */
extern int solved;

/** Element of the doubly linked list. */
typedef struct DLLElement {
	/** Useful data. */
	int data;
	/** Pointer to the previous element in the list. */
	struct DLLElement *previousElement;
	/** Pointer to the next element in the list. */
	struct DLLElement *nextElement;
} *DLLElementPtr;

/** Doubly linked list. */
typedef struct {
	/** Pointer to the first element in the list. */
	DLLElementPtr firstElement;
	/** Pointer to the current element in the list. */
	DLLElementPtr activeElement;
	/** Pointer to the last element in the list. */
	DLLElementPtr lastElement;
} DLList;

void DLL_Init( DLList * );

void DLL_Dispose( DLList * );

void DLL_InsertFirst( DLList *, int );

void DLL_InsertLast( DLList *, int );

void DLL_First( DLList * );

void DLL_Last( DLList * );

void DLL_GetFirst( DLList *, int * );

void DLL_GetLast( DLList *, int * );

void DLL_DeleteFirst( DLList * );

void DLL_DeleteLast( DLList * );

void DLL_DeleteAfter( DLList * );

void DLL_DeleteBefore( DLList * );

void DLL_InsertAfter( DLList *, int );

void DLL_InsertBefore( DLList *, int );

void DLL_GetValue( DLList *, int * );

void DLL_SetValue( DLList *, int );

void DLL_Next( DLList * );

void DLL_Previous( DLList * );

int DLL_IsActive( DLList * );

/* End of c206.h */
