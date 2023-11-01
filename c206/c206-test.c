
/* ***************************** c206-test.c ******************************** */
/*  Course: Algorithms (IAL) - FIT VUT in Brno                                */
/*  Task: c206 - Create a doubly linked linear list						      */
/*  Created: Martin Tuček, September 2005				                      */
/*  Modified by: Kamil Jeřábek, September 2019                                */
/*               Daniel Dolejška, September 2021                              */
/* ************************************************************************** */

#include "c206.h"

DLList TEMPLIST;
int ElemValue = 1;
/* Handles wrongly linked lists. */
int MaxListLength = 100;

/*******************************************************************************
 * Helper functions facilitating the testing of custom implementation.
 ******************************************************************************/

void print_elements_of_list( DLList TL ) {
	DLList TempList = TL;
	int CurrListLength = 0;
	printf("-----------------");
	while ((TempList.firstElement != NULL) && (CurrListLength < MaxListLength))
	{
		printf("\n \t%d", TempList.firstElement->data);
		if ((TempList.firstElement == TL.activeElement) && (TL.activeElement != NULL))
			printf("\t <= this is the active element ");
		TempList.firstElement = TempList.firstElement->nextElement;
		CurrListLength++;
	}
	if (CurrListLength >= MaxListLength)
		printf("\nList exceeded maximum length!");
	printf("\n-----------------\n");
}

int test_DLL_Init() {
	solved = TRUE;
	DLL_Init(&TEMPLIST);
	if (!solved)
	{
		printf("Operation List_Init was not implemented!\n");
		return (FALSE);
	}
	else
	{
		print_elements_of_list(TEMPLIST);
		return (TRUE);
	}
}

int test_DLL_Dispose() {
	solved = TRUE;
	DLL_Dispose(&TEMPLIST);
	if (!solved)
	{
		printf("Operation DLL_Dispose was not implemented!\n");
		return (FALSE);
	}
	else
	{
		print_elements_of_list(TEMPLIST);
		return (TRUE);
	}
}

int test_DLL_InsertFirst() {
	solved = TRUE;
	DLL_InsertFirst(&TEMPLIST, ElemValue);
	if (!solved)
	{
		printf("Operation DLL_InsertFirst was not implemented!\n");
		return (FALSE);
	}
	else
	{
		print_elements_of_list(TEMPLIST);
		return (TRUE);
	}
}

int test_DLL_InsertLast() {
	solved = TRUE;
	DLL_InsertLast(&TEMPLIST, ElemValue);
	if (!solved)
	{
		printf("Operation DLL_InsertLast was not implemented!\n");
		return (FALSE);
	}
	else
	{
		print_elements_of_list(TEMPLIST);
		return (TRUE);
	}
}

int test_DLL_First() {
	solved = TRUE;
	DLL_First(&TEMPLIST);
	if (!solved)
	{
		printf("Operation DLL_First was not implemented!\n");
		return (FALSE);
	}
	else
	{
		print_elements_of_list(TEMPLIST);
		return (TRUE);
	}
}

int test_DLL_Last() {
	solved = TRUE;
	DLL_Last(&TEMPLIST);
	if (!solved)
	{
		printf("Operation DLL_Last was not implemented!\n");
		return (FALSE);
	}
	else
	{
		print_elements_of_list(TEMPLIST);
		return (TRUE);
	}
}

int test_DLL_GetFirst() {
	solved = TRUE;
	int temp;
	DLL_GetFirst(&TEMPLIST, &temp);
	if (!solved)
	{
		printf("Operation DLL_GetFirst was not implemented!\n");
		return (FALSE);
	}
	else
	{
		if (error_flag)
		{
			printf("Operation DLL_GetFirst called function DLL_Error.\n");
			error_flag = FALSE;
			return (FALSE);
		}
		else
		{
			printf("Operation DLL_GetFirst returns content %d.\n", temp);
			return (TRUE);
		}
	}
}

int test_DLL_GetLast() {
	solved = TRUE;
	int temp;
	DLL_GetLast(&TEMPLIST, &temp);
	if (!solved)
	{
		printf("Operation DLL_GetLast was not implemented!\n");
		return (FALSE);
	}
	else
	{
		if (error_flag)
		{
			printf("Operation DLL_GetLast called function DLL_Error.\n");
			error_flag = FALSE;
			return (FALSE);
		}
		else
		{
			printf("Operation DLL_GetLast returns content %d.\n", temp);
			return (TRUE);
		}
	}
}

int test_DLL_DeleteFirst() {
	solved = TRUE;
	DLL_DeleteFirst(&TEMPLIST);
	if (!solved)
	{
		printf("Operation DLL_DeleteFirst was not implemented!\n");
		return (FALSE);
	}
	else
	{
		print_elements_of_list(TEMPLIST);
		return (TRUE);
	}
}

int test_DLL_DeleteLast() {
	solved = TRUE;
	DLL_DeleteLast(&TEMPLIST);
	if (!solved)
	{
		printf("Operation DLL_DeleteLast was not implemented!\n");
		return (FALSE);
	}
	else
	{
		print_elements_of_list(TEMPLIST);
		return (TRUE);
	}
}

int test_DLL_DeleteAfter() {
	solved = TRUE;
	DLL_DeleteAfter(&TEMPLIST);
	if (!solved)
	{
		printf("Operation DLL_DeleteAfter was not implemented!\n");
		return (FALSE);
	}
	else
	{
		print_elements_of_list(TEMPLIST);
		return (TRUE);
	}
}

int test_DLL_DeleteBefore() {
	solved = TRUE;
	DLL_DeleteBefore(&TEMPLIST);
	if (!solved)
	{
		printf("Operation DLL_DeleteBefore was not implemented!\n");
		return (FALSE);
	}
	else
	{
		print_elements_of_list(TEMPLIST);
		return (TRUE);
	}
}

int test_DLL_InsertAfter() {
	solved = TRUE;
	DLL_InsertAfter(&TEMPLIST, ElemValue);
	if (!solved)
	{
		printf("Operation DLL_InsertAfter was not implemented!\n");
		return (FALSE);
	}
	else
	{
		print_elements_of_list(TEMPLIST);
		return (TRUE);
	}
}

int test_DLL_InsertBefore() {
	solved = TRUE;
	DLL_InsertBefore(&TEMPLIST, ElemValue);
	if (!solved)
	{
		printf("Operation DLL_InsertBefore was not implemented!\n");
		return (FALSE);
	}
	else
	{
		print_elements_of_list(TEMPLIST);
		return (TRUE);
	}
}

int test_DLL_GetValue() {
	solved = TRUE;
	int temp;
	DLL_GetValue(&TEMPLIST, &temp);

	if (!solved)
	{
		printf("Operation DLL_GetValue was not implemented!\n");
		return (FALSE);
	}
	else
	{
		if (error_flag)
		{
			printf("Operation DLL_GetValue called function DLL_Error.\n");
			error_flag = FALSE;
			return (FALSE);
		}
		else
		{
			printf("Operation DLL_GetValue returns content %d.\n", temp);
			return (TRUE);
		}
	}
}

int test_DLL_SetValue() {
	solved = TRUE;
	DLL_SetValue(&TEMPLIST, ElemValue);
	if (!solved)
	{
		printf("Operation DLL_SetValue was not implemented!\n");
		return (FALSE);
	}
	else
	{
		print_elements_of_list(TEMPLIST);
		return (TRUE);
	}
}

int test_DLL_Next() {
	solved = TRUE;
	DLL_Next(&TEMPLIST);
	if (!solved)
	{
		printf("Operation DLL_Next was not implemented!\n");
		return (FALSE);
	}
	else
	{
		print_elements_of_list(TEMPLIST);
		return (TRUE);
	}
}

int test_DLL_Previous() {
	solved = TRUE;
	DLL_Previous(&TEMPLIST);
	if (!solved)
	{
		printf("Operation DLL_Previous was not implemented!\n");
		return (FALSE);
	}
	else
	{
		print_elements_of_list(TEMPLIST);
		return (TRUE);
	}
}

int test_DLL_IsActive() {
	solved = TRUE;
	int tmp = DLL_IsActive(&TEMPLIST);
	if (!solved)
	{
		printf("Operation DLL_IsActive was not implemented!\n");
		return (FALSE);
	}
	else
	{
		if (tmp)
			printf("Operation DLL_IsActive returns value true.\n");
		else
			printf("Operation DLL_IsActive returns value false.\n");
		return (TRUE);
	}
}

/*******************************************************************************
 * BASIC TESTS
 * ---------- 
 * By successfully passing these tests, the student will earn the first set of points for the assignment.
 * However, during grading, extended tests will be used, which will also focus on edge cases. 
 * Therefore, it is recommended that each student tries to expand these basic tests with other interesting scenarios.
 *  
 ******************************************************************************/

int main() {
	printf("C206 - Doubly Linked List - Basic Tests\n");
	printf("---------------------------------------\n");

	printf("\n[TEST01]\n");
	printf("List initialization\n");
	printf("~~~~~~~~~~~~~~~~~~~~\n");
	test_DLL_Init();

	printf("\n[TEST02]\n");
	printf("We will call the DLL_InsertFirst operation 2 times and the DLL_InsertLast operation 2 times.\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	ElemValue = 1;
	test_DLL_InsertFirst();
	ElemValue = 2;
	test_DLL_InsertFirst();
	ElemValue = 3;
	test_DLL_InsertLast();
	ElemValue = 4;
	test_DLL_InsertLast();

	printf("\n[TEST03]\n");
	printf("We will test the DLL_First function with an inactive list and the DLL_IsActive function.\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	test_DLL_First();
	test_DLL_IsActive();

	printf("\n[TEST04]\n");
	printf("We will test the DLL_Last function.\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	test_DLL_Last();
	test_DLL_IsActive();

	printf("\n[TEST05]\n");
	printf("Test the DLL_GetValue function with activity on the last item\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	test_DLL_GetValue();

	printf("\n[TEST06]\n");
	printf("Test the DLL_Previous function - we will call it 3 times, activity will remain on the first item.\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	test_DLL_Previous();
	test_DLL_Previous();
	test_DLL_Previous();
	test_DLL_IsActive();

	printf("\n[TEST07]\n");
	printf("Update the content of the active item.\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	ElemValue = 5;
	test_DLL_SetValue();
	test_DLL_IsActive();
	test_DLL_GetValue();

	printf("\n[TEST08]\n");
	printf("Test the DLL_Next function - we will call it 3 times, activity will remain on the last item.\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	test_DLL_Next();
	test_DLL_Next();
	test_DLL_Next();
	test_DLL_IsActive();

	printf("\n[TEST09]\n");
	printf("We will perform DLL_Next once more - activity will be lost.\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	test_DLL_Next();
	test_DLL_IsActive();

	printf("\n[TEST10]\n");
	printf("We will set activity to the beginning and then cancel it with the DLL_Previous operation.\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	test_DLL_First();
	test_DLL_Previous();
	test_DLL_IsActive();

	printf("\n[TEST11]\n");
	printf("Attempt to use DLL_GetValue with an inactive list => handled error.\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	test_DLL_GetValue();

	printf("\n[TEST12]\n");
	printf("Use the DLL_GetFirst operation with an inactive list\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	test_DLL_GetFirst();

	printf("\n[TEST13]\n");
	printf("Use the DLL_GetLast operation with an inactive list\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	test_DLL_GetLast();

	printf("\n[TEST14]\n");
	printf("Use the DLL_DeleteFirst operation with an inactive list\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	test_DLL_DeleteFirst();
	test_DLL_IsActive();

	printf("\n[TEST15]\n");
	printf("Use the DLL_DeleteLast operation with an inactive list\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	test_DLL_DeleteLast();
	test_DLL_IsActive();

	printf("\n[TEST16]\n");
	printf("We will try DLL_DeleteAfter with activity on the last item.\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	test_DLL_Last();
	test_DLL_DeleteAfter();
	test_DLL_IsActive();

	printf("\n[TEST17]\n");
	printf("The DLL_DeleteBefore operation will now delete the first item.\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	test_DLL_DeleteBefore();
	test_DLL_IsActive();

	printf("\n[TEST18]\n");
	printf("Finally, we will dispose of the list.\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~\n");
	test_DLL_Dispose();
	test_DLL_IsActive();

	printf("\n----- C206 - The End of Basic Tests -----\n");

	return (0);
}

/* End of c206-test.c */
