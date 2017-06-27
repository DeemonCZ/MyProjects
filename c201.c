
/* c201.c *********************************************************************}
{* Téma: Jednosměrný lineární seznam
**
**                     Návrh a referenční implementace: Petr Přikryl, říjen 1994
**                                          Úpravy: Andrea Němcová listopad 1996
**                                                   Petr Přikryl, listopad 1997
**                                Přepracované zadání: Petr Přikryl, březen 1998
**                                  Přepis do jazyka C: Martin Tuček, říjen 2004
**                                            Úpravy: Bohuslav Křena, říjen 2016
**
** Implementujte abstraktní datový typ jednosměrný lineární seznam.
** Užitečným obsahem prvku seznamu je celé číslo typu int.
** Seznam bude jako datová abstrakce reprezentován proměnnou typu tList.
** Definici konstant a typů naleznete v hlavičkovém souboru c201.h.
** 
** Vaším úkolem je implementovat následující operace, které spolu s výše
** uvedenou datovou částí abstrakce tvoří abstraktní datový typ tList:
**
**      InitList ...... inicializace seznamu před prvním použitím,
**      DisposeList ... zrušení všech prvků seznamu,
**      InsertFirst ... vložení prvku na začátek seznamu,
**      First ......... nastavení aktivity na první prvek,
**      CopyFirst ..... vrací hodnotu prvního prvku,
**      DeleteFirst ... zruší první prvek seznamu,
**      PostDelete .... ruší prvek za aktivním prvkem,
**      PostInsert .... vloží nový prvek za aktivní prvek seznamu,
**      Copy .......... vrací hodnotu aktivního prvku,
**      Actualize ..... přepíše obsah aktivního prvku novou hodnotou,
**      Succ .......... posune aktivitu na další prvek seznamu,
**      Active ........ zjišťuje aktivitu seznamu.
**
** Při implementaci funkcí nevolejte žádnou z funkcí implementovaných v rámci
** tohoto příkladu, není-li u dané funkce explicitně uvedeno něco jiného.
**
** Nemusíte ošetřovat situaci, kdy místo legálního ukazatele na seznam 
** předá někdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodně komentujte!
**
** Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
** Proto zde používáme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako
** procedury (v jazyce C procedurám odpovídají funkce vracející typ void).
**/

#include "c201.h"

int solved;
int errflg;

void Error() {
/*
** Vytiskne upozornění na to, že došlo k chybě.
** Tato funkce bude volána z některých dále implementovaných operací.
**/
    printf("*ERROR* The program has performed an illegal operation.\n");
    errflg = TRUE;                      /* globální proměnná -- příznak chyby */
}

void InitList(tList *L) {
/*
** Provede inicializaci seznamu L před jeho prvním použitím (tzn. žádná
** z následujících funkcí nebude volána nad neinicializovaným seznamem).
** Tato inicializace se nikdy nebude provádět nad již inicializovaným
** seznamem, a proto tuto možnost neošetřujte. Vždy předpokládejte,
** že neinicializované proměnné mají nedefinovanou hodnotu.
**/
    L->First = NULL;            //inicializace prázdného seznamu
    L->Act = L->First;          //a defaultní nastavení proměnných

}

void DisposeList(tList *L) {
/*
** Zruší všechny prvky seznamu L a uvede seznam L do stavu, v jakém se nacházel
** po inicializaci. Veškerá paměť používaná prvky seznamu L bude korektně
** uvolněna voláním operace free.
***/

    while (L->First != NULL) {          //když seznam neni prázdný,
        tElemPtr help = L->First;       //tak postupně maže prvky seznamu
        L->First = L->First->ptr;       //v pořadí od začátku, dokud nezbude prázdný seznam
        free(help);
    }
}

void InsertFirst(tList *L, int val) {
/*
** Vloží prvek s hodnotou val na začátek seznamu L.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci Error().
**/
    tElemPtr help = malloc(sizeof(struct tElem));

    if (help != NULL) {             //pokud je v paměti místo,
        help->data = val;           //definuje pomocnou proměnnou "help"
        help->ptr = L->First;       //a vloží ji na začátek seznamu
        L->First = help;
    }
    else {
        Error();
    }

}

void First(tList *L) {
/*
** Nastaví aktivitu seznamu L na jeho první prvek.
** Funkci implementujte jako jediný příkaz, aniž byste testovali,
** zda je seznam L prázdný.
**/

    L->Act = L->First;      // přiřadí aktivní na první prvek v seznamu

}

void CopyFirst(tList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu prvního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci Error().
**/

    if (L->First != NULL) {
        *val = L->First->data;          //pokud neni prázdný, vrátí data z prvniho prvku
    }
    else {
        Error();
    }

}

void DeleteFirst(tList *L) {
/*
** Zruší první prvek seznamu L a uvolní jím používanou paměť.
** Pokud byl rušený prvek aktivní, aktivita seznamu se ztrácí.
** Pokud byl seznam L prázdný, nic se neděje.
**/


    if (L->First != NULL) {             //když seznam neni prázdný,
        tElemPtr help = L->First;       //vymaže první prvek seznamu
        if (L->First == L->Act) {       //a nastaví následující jako první
            L->Act = NULL;
        }
        L->First = L->First->ptr;
        free(help);
    }

}

void PostDelete(tList *L) {
/* 
** Zruší prvek seznamu L za aktivním prvkem a uvolní jím používanou paměť.
** Pokud není seznam L aktivní nebo pokud je aktivní poslední prvek seznamu L,
** nic se neděje.
**/

    if (L->Act->ptr != NULL && L->Act != NULL) {        //pokud je to možné,
        tElemPtr help = L->Act->ptr;                    //zruší následující prvek za aktivním
        L->Act->ptr = help->ptr;
        free(help);
    }

}

void PostInsert(tList *L, int val) {
/*
** Vloží prvek s hodnotou val za aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje!
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** zavolá funkci Error().
**/

    if (L->Act != NULL) {                                   //pokud je seznam aktivní,
        tElemPtr help = malloc(sizeof(struct tElem));       //vloží pomocný prvek "help"
        if (help != NULL) {                                 //za aktivní prvek v seznamu
            help->ptr = L->Act->ptr;
            L->Act->ptr = help;
            L->Act->ptr->data = val;
        }
        else {
            Error();
        }
    }
}

void Copy(tList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu aktivního prvku seznamu L.
** Pokud seznam není aktivní, zavolá funkci Error().
**/

    if (L->Act != NULL) {           //pokud je sezam aktivní,
        *val = L->Act->data;        //skopíruje hodnotu z aktivního prvku
    }                               //do proměnné "val"
    else {
        Error();
    }

}

void Actualize(tList *L, int val) {
/*
** Přepíše data aktivního prvku seznamu L hodnotou val.
** Pokud seznam L není aktivní, nedělá nic!
**/

    if (L->Act != NULL) {           //pokud je seznam aktivní,
        L->Act->data = val;         //vloží data z "val" na pozici aktivního prvku
    }

}

void Succ(tList *L) {
/*
** Posune aktivitu na následující prvek seznamu L.
** Všimněte si, že touto operací se může aktivní seznam stát neaktivním.
** Pokud není předaný seznam L aktivní, nedělá funkce nic.
**/

    if (L->Act != NULL) {           //pokud je seznam aktivní,
        L->Act = L->Act->ptr;       //posune aktivitu o jednu pozici dál
    }

}

int Active(tList *L) {
/*
** Je-li seznam L aktivní, vrací nenulovou hodnotu, jinak vrací 0.
** Tuto funkci je vhodné implementovat jedním příkazem return. 
**/

    if (L->Act == NULL) {           //pokud je seznam neaktivní,
        return 0;                   //vrátí 0, jinak 1 (nenulovou hodnotu)
    }
	else
		return 1;
}

/* Konec c201.c */
