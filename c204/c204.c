
/* ******************************* c204.c *********************************** */
/*  Předmět: Algoritmy (IAL) - FIT VUT v Brně                                 */
/*  Úkol: c204 - Převod infixového výrazu na postfixový (s využitím c202)     */
/*  Referenční implementace: Petr Přikryl, listopad 1994                      */
/*  Přepis do jazyka C: Lukáš Maršík, prosinec 2012                           */
/*  Upravil: Kamil Jeřábek, září 2019                                         */
/*           Daniel Dolejška, září 2021                                       */
/* ************************************************************************** */
/*
** Implementujte proceduru pro převod infixového zápisu matematického výrazu
** do postfixového tvaru. Pro převod využijte zásobník (Stack), který byl
** implementován v rámci příkladu c202. Bez správného vyřešení příkladu c202
** se o řešení tohoto příkladu nepokoušejte.
**
** Implementujte následující funkci:
**
**    infix2postfix ... konverzní funkce pro převod infixového výrazu
**                      na postfixový
**
** Pro lepší přehlednost kódu implementujte následující pomocné funkce:
**
**    untilLeftPar ... vyprázdnění zásobníku až po levou závorku
**    doOperation .... zpracování operátoru konvertovaného výrazu
**
** Své řešení účelně komentujte.
**
** Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
** Proto zde používáme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako procedury
** (v jazyce C procedurám odpovídají funkce vracející typ void).
**
**/

#include "../c204/c204.h"
#include <string.h>

int solved;


/**
 * Pomocná funkce untilLeftPar.
 * Slouží k vyprázdnění zásobníku až po levou závorku, přičemž levá závorka bude
 * také odstraněna.
 * Pokud je zásobník prázdný, provádění funkce se ukončí.
 *
 * Operátory odstraňované ze zásobníku postupně vkládejte do výstupního pole
 * znaků postfixExpression.
 * Délka převedeného výrazu a též ukazatel na první volné místo, na které se má
 * zapisovat, představuje parametr postfixExpressionLength.
 *
 * Aby se minimalizoval počet přístupů ke struktuře zásobníku, můžete zde
 * nadeklarovat a používat pomocnou proměnnou typu char.
 *
 * @param stack Ukazatel na inicializovanou strukturu zásobníku
 * @param postfixExpression Znakový řetězec obsahující výsledný postfixový výraz
 * @param postfixExpressionLength Ukazatel na aktuální délku výsledného
 * postfixového výrazu
 */
void untilLeftPar(Stack *stack, char *postfixExpression,
                  unsigned *postfixExpressionLength) {}

/**
 * Pomocná funkce doOperation.
 * Zpracuje operátor, který je předán parametrem c po načtení znaku ze
 * vstupního pole znaků.
 *
 * Dle priority předaného operátoru a případně priority operátoru na vrcholu
 * zásobníku rozhodneme o dalším postupu.
 * Délka převedeného výrazu a taktéž ukazatel na první volné místo, do kterého
 * se má zapisovat, představuje parametr postfixExpressionLength, výstupním
 * polem znaků je opět postfixExpression.
 *
 * @param stack Ukazatel na inicializovanou strukturu zásobníku
 * @param c Znak operátoru ve výrazu
 * @param postfixExpression Znakový řetězec obsahující výsledný postfixový výraz
 * @param postfixExpressionLength Ukazatel na aktuální délku výsledného
 * postfixového výrazu
 */
void doOperation(Stack *stack, char c, char *postfixExpression,
                 unsigned *postfixExpressionLength) {

    char top;

    // Pokud zásobnik je prázdný
    if (Stack_IsEmpty(stack) ||
        // nebo na vrcholu je levá závorka
        (Stack_Top(stack, &top), top == '(') ||
        // nebo na vrcholu je operator s nízší prioritou
        (strchr("+-", top) != NULL && strchr("/*", c) != NULL)) {

        Stack_Push(stack, c);
    // jinak vlož vrhol zásobníku do výsledného řetězce a zavolej funkci znova
    } else {
        postfixExpression[*postfixExpressionLength] = top;
        (*postfixExpressionLength)++;
        Stack_Pop(stack);
        doOperation(stack, c, postfixExpression, postfixExpressionLength);
    }
}

/**
 * Konverzní funkce infix2postfix.
 * Čte infixový výraz ze vstupního řetězce infixExpression a generuje
 * odpovídající postfixový výraz do výstupního řetězce (postup převodu hledejte
 * v přednáškách nebo ve studijní opoře).
 * Paměť pro výstupní řetězec (o velikosti MAX_LEN) je třeba alokovat. Volající
 * funkce, tedy příjemce konvertovaného řetězce, zajistí korektní uvolnění zde
 * alokované paměti.
 *
 * Tvar výrazu:
 * 1. Výraz obsahuje operátory + - * / ve významu sčítání, odčítání,
 *    násobení a dělení. Sčítání má stejnou prioritu jako odčítání,
 *    násobení má stejnou prioritu jako dělení. Priorita násobení je
 *    větší než priorita sčítání. Všechny operátory jsou binární
 *    (neuvažujte unární mínus).
 *
 * 2. Hodnoty ve výrazu jsou reprezentovány jednoznakovými identifikátory
 *    a číslicemi - 0..9, a..z, A..Z (velikost písmen se rozlišuje).
 *
 * 3. Ve výrazu může být použit předem neurčený počet dvojic kulatých
 *    závorek. Uvažujte, že vstupní výraz je zapsán správně (neošetřujte
 *    chybné zadání výrazu).
 *
 * 4. Každý korektně zapsaný výraz (infixový i postfixový) musí být uzavřen
 *    ukončovacím znakem '='.
 *
 * 5. Při stejné prioritě operátorů se výraz vyhodnocuje zleva doprava.
 *
 * Poznámky k implementaci
 * -----------------------
 * Jako zásobník použijte zásobník znaků Stack implementovaný v příkladu c202.
 * Pro práci se zásobníkem pak používejte výhradně operace z jeho rozhraní.
 *
 * Při implementaci využijte pomocné funkce untilLeftPar a doOperation.
 *
 * Řetězcem (infixového a postfixového výrazu) je zde myšleno pole znaků typu
 * char, jenž je korektně ukončeno nulovým znakem dle zvyklostí jazyka C.
 *
 * Na vstupu očekávejte pouze korektně zapsané a ukončené výrazy. Jejich délka
 * nepřesáhne MAX_LEN-1 (MAX_LEN i s nulovým znakem) a tedy i výsledný výraz
 * by se měl vejít do alokovaného pole. Po alokaci dynamické paměti si vždycky
 * ověřte, že se alokace skutečně zdrařila. V případě chyby alokace vraťte
 * namísto řetězce konstantu NULL.
 *
 * @param infixExpression Znakový řetězec obsahující infixový výraz k převedení
 *
 * @returns Znakový řetězec obsahující výsledný postfixový výraz
 */
char *infix2postfix(const char *infixExpression) {

    Stack *stack = (Stack *) malloc(sizeof(Stack));
    Stack_Init(stack);

    // alokujeme tolik pamětí kolik zabíra vstupní řetězec
    char *result = (char *) malloc(sizeof(char) * MAX_LEN);
    if (result == NULL) {
        return NULL;
    }

    unsigned int i = 0;// pro procházení vstupem
    unsigned int j = 0;// pro zapisování do výstupu

    // Zpracování operandů
    while (infixExpression[i] != '\0') {
        if ((infixExpression[i] >= 'a' && infixExpression[i] <= 'z') ||
            (infixExpression[i] >= 'A' && infixExpression[i] <= 'Z') ||
            (infixExpression[i] >= '0' && infixExpression[i] <= '9')) {

            result[j] = infixExpression[i];
            j++;
        }

        // Zprocování závorek
        if (infixExpression[i] == '(') {
            Stack_Push(stack, infixExpression[i]);
        }

        if (infixExpression[i] == ')') {
            char c = '\0';
            Stack_Top(stack, &c);
            Stack_Pop(stack);
            while (c != '(') {
                result[j] = c;
                j++;
                Stack_Top(stack, &c);
                Stack_Pop(stack);
            };
        }

        // Zpracování operatorů
        if (strchr("+-/*", infixExpression[i]) != NULL) {
            doOperation(stack, infixExpression[i], result, &j);
        }

        // Zpracování omezovače (rovnítka)
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

    // Uvolňujeme alokovaný zásobník
    while (!Stack_IsEmpty(stack)) {
        Stack_Pop(stack);
    }
    free(stack);

    return result;
}

/* Konec c204.c */
