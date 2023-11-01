/* ******************************* c204.h *********************************** */
/*  Course: Algorithms (IAL) - FIT VUT in Brno                               */
/*  Assignment: c204 - Conversion of infix expression to postfix (using c202) */
/*  Reference implementation: Petr Přikryl, November 1994                     */
/*  Rewritten in C language: Lukáš Maršík, December 2012                      */
/*  Modified by: Kamil Jeřábek, September 2019                                */
/*              Daniel Dolejška, September 2021                               */
/* ************************************************************************** */

/* PLEASE DO NOT MODIFY THIS FILE! */

#ifndef _INFIX2POSTFIX_H_
#define _INFIX2POSTFIX_H_

#define FALSE 0
#define TRUE 1

#include <stdio.h>
#include <stdlib.h>

/** Utilizes the example c202 - stack. */
#include "../c202/c202.h"

/** Maximum length of the expression string. */
#define MAX_LEN 64

/** Global variable - indicates whether the operation was solved. */
extern int solved;

char *infix2postfix( const char *infixExpression );

#endif

/* End of header file c204.h */
