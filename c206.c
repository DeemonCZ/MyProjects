	
/* c206.c **********************************************************}
{* Téma: Dvousměrně vázaný lineární seznam
**
**                   Návrh a referenční implementace: Bohuslav Křena, říjen 2001
**                            Přepracované do jazyka C: Martin Tuček, říjen 2004
**                                            Úpravy: Bohuslav Křena, říjen 2016
**
**Projekt: Dominik Chuchma
**
** Implementujte abstraktní datový typ dvousměrně vázaný lineární seznam.
** Užitečným obsahem prvku seznamu je hodnota typu int.
** Seznam bude jako datová abstrakce reprezentován proměnnou
** typu tDLList (DL znamená Double-Linked a slouží pro odlišení
** jmen konstant, typů a funkcí od jmen u jednosměrně vázaného lineárního
** seznamu). Definici konstant a typů naleznete v hlavičkovém souboru c206.h.
**
** Vaším úkolem je implementovat následující operace, které spolu
** s výše uvedenou datovou částí abstrakce tvoří abstraktní datový typ
** obousměrně vázaný lineární seznam:
**
**      DLInitList ...... inicializace seznamu před prvním použitím,
**      DLDisposeList ... zrušení všech prvků seznamu,
**      DLInsertFirst ... vložení prvku na začátek seznamu,
**      DLInsertLast .... vložení prvku na konec seznamu,
**      DLFirst ......... nastavení aktivity na první prvek,
**      DLLast .......... nastavení aktivity na poslední prvek,
**      DLCopyFirst ..... vrací hodnotu prvního prvku,
**      DLCopyLast ...... vrací hodnotu posledního prvku,
**      DLDeleteFirst ... zruší první prvek seznamu,
**      DLDeleteLast .... zruší poslední prvek seznamu,
**      DLPostDelete .... ruší prvek za aktivním prvkem,
**      DLPreDelete ..... ruší prvek před aktivním prvkem,
**      DLPostInsert .... vloží nový prvek za aktivní prvek seznamu,
**      DLPreInsert ..... vloží nový prvek před aktivní prvek seznamu,
**      DLCopy .......... vrací hodnotu aktivního prvku,
**      DLActualize ..... přepíše obsah aktivního prvku novou hodnotou,
**      DLSucc .......... posune aktivitu na další prvek seznamu,
**      DLPred .......... posune aktivitu na předchozí prvek seznamu,
**      DLActive ........ zjišťuje aktivitu seznamu.
**
** Při implementaci jednotlivých funkcí nevolejte žádnou z funkcí
** implementovaných v rámci tohoto příkladu, není-li u funkce
** explicitně uvedeno něco jiného.
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

#include "c206.h"

int solved;
int errflg;

void DLError() {
/*
** Vytiskne upozornění na to, že došlo k chybě.
** Tato funkce bude volána z některých dále implementovaných operací.
**/	
    printf ("*ERROR* The program has performed an illegal operation.\n");
    errflg = TRUE;             /* globální proměnná -- příznak ošetření chyby */
    return;
}

void DLInitList (tDLList *L) {
/*
** Provede inicializaci seznamu L před jeho prvním použitím (tzn. žádná
** z následujících funkcí nebude volána nad neinicializovaným seznamem).
** Tato inicializace se nikdy nebude provádět nad již inicializovaným
** seznamem, a proto tuto možnost neošetřujte. Vždy předpokládejte,
** že neinicializované proměnné mají nedefinovanou hodnotu.
**/

    L->First = NULL;        //inicializace prázdného seznamu
    L->Act = L->First;      //a defaultní nastavení ukazatelů
    L->Last = L->Act;
}

void DLDisposeList (tDLList *L) {
/*
** Zruší všechny prvky seznamu L a uvede seznam do stavu, v jakém
** se nacházel po inicializaci. Rušené prvky seznamu budou korektně
** uvolněny voláním operace free. 
**/
    while (L->First != NULL) {          //maže s pomocným ukazatelem prvek
        tDLElemPtr help = L->First;     //před prvním v seznamu, dokud
        L->First = L->First->rptr;      //nezbude jen první prázdný prvek
        free(help);
    }
    L->Act = NULL;
}

void DLInsertFirst (tDLList *L, int val) {
/*
** Vloží nový prvek na začátek seznamu L.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/
	tDLElemPtr help = malloc(sizeof(struct tDLElem));

    if (help != NULL) {                 //vloží prvek help před první prvek,
        help->data = val;               //vhodně propojí a přesune ukazatel
        if (L->First != NULL){          //"first" na začátek seznamu
            L->First->lptr = help;      //pokud je seznam prázdný, nastaví i last
        }
        help->rptr = L->First;
        L->First = help;
        help->lptr = NULL;
        if (L->Last == NULL){
            L->Last = help;
        }
    }
    else {
            DLError();
    }
}

void DLInsertLast(tDLList *L, int val) {
/*
** Vloží nový prvek na konec seznamu L (symetrická operace k DLInsertFirst).
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/

    tDLElemPtr help = malloc(sizeof(struct tDLElem));

    if (help != NULL) {                 //vloží prvek help za poslední prvek
        help->data = val;               //vhodně propojí a přesune ukazatel
        if (L->Last != NULL){           //"last" na konec seznamu
            L->Last->rptr = help;       //pokud je seznam prázdný, nastaví i first
        }
        help->lptr = L->Last;
        help->rptr = NULL;
        if (L->First == NULL){
            L->First = help;
        }
        L->Last = help;
    }
    else {
            DLError();
    }
}

void DLFirst (tDLList *L) {
/*
** Nastaví aktivitu na první prvek seznamu L.
** Funkci implementujte jako jediný příkaz (nepočítáme-li return),
** aniž byste testovali, zda je seznam L prázdný.
**/

    L->Act = L->First;      //nastaví aktivitu na krví prvek seznamu

}

void DLLast (tDLList *L) {
/*
** Nastaví aktivitu na poslední prvek seznamu L.
** Funkci implementujte jako jediný příkaz (nepočítáme-li return),
** aniž byste testovali, zda je seznam L prázdný.
**/
	
	L->Act = L->Last;       //Nastaví aktivitu na poslední prvek seznamu

}

void DLCopyFirst (tDLList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu prvního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/

    if (L->First != NULL) {         //pokud seznam neni prázdný, vrátí
        *val = L->First->data;      //v parametru val hodnotu prvního prvku
    }
    else {
            DLError();
    }
}

void DLCopyLast (tDLList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu posledního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/

    if (L->Last != NULL) {          //pokud seznam neni prázdný, vrátí
        *val = L->Last->data;       //v parametru val hodnotu posledního prvku
    }
    else {
        DLError();
    }
}

void DLDeleteFirst (tDLList *L) {
/*
** Zruší první prvek seznamu L. Pokud byl první prvek aktivní, aktivita 
** se ztrácí. Pokud byl seznam L prázdný, nic se neděje.
**/
    if (L->First != NULL){                  //přesune ukazatel "first" následující prvek
        tDLElemPtr help = L->First;         // a smaže bývalý první prvek
        L->First = L->First->rptr;
        if (L->First->lptr != NULL){
        L->First->lptr = NULL;
        }

        free(help);
    }
}	

void DLDeleteLast (tDLList *L) {
/*
** Zruší poslední prvek seznamu L. Pokud byl poslední prvek aktivní,
** aktivita seznamu se ztrácí. Pokud byl seznam L prázdný, nic se neděje.
**/ 
	if (L->First != NULL){                  //přesune ukazatel "last" na předchozí prvek
        tDLElemPtr help = L->Last;          //a smaže bývalý poslední prvek
        L->Last = L->Last->lptr;
        if (L->Last->rptr != NULL){
            L->Last->rptr = NULL;
        }
        free(help);
    }
}

void DLPostDelete (tDLList *L) {
/*
** Zruší prvek seznamu L za aktivním prvkem.
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** posledním prvkem seznamu, nic se neděje.
**/
    if (L->Act != NULL && L->Act != L->Last){   //pokud je seznam aktivní a pokud neni "Act"
        tDLElemPtr help = L->Act->rptr;         //posledním prvkem  seznamu, smaže prvek za aktivním
        help->rptr->lptr = L->Act;              //a vhodně propojí ukazatele
        L->Act->rptr = help->rptr;
        free(help);
    }
}

void DLPreDelete (tDLList *L) {
/*
** Zruší prvek před aktivním prvkem seznamu L .
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** prvním prvkem seznamu, nic se neděje.
**/
	if (L->Act != NULL && L->Act != L->First){  //pokud je seznam aktivní a pokud neni "Act"
        tDLElemPtr help = L->Act->lptr;         //prvním prvkem seznamu, smaže prvek před aktivním
        if (L->First != L->Act->lptr) {         //a vhodně propojí ukazatele
            help->lptr->rptr = L->Act;
            L->Act->lptr = help->lptr;
        }
        L->First = L->First->rptr;
        free(help);
    }
}

void DLPostInsert (tDLList *L, int val) {
/*
** Vloží prvek za aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/
    tDLElemPtr help = malloc(sizeof(struct tDLElem));

    if (help != NULL){                      //když je dostatek místa v paměti
        if (L->Act != NULL) {               //a když je seznam aktivní,
            help->data = val;               //vloží prvek help za aktivní prvek
            L->Act->rptr->lptr = help;      //a vhodně propojí ukazatele
            help->rptr = L->Act->rptr;
            L->Act->rptr = help;
            help->lptr = L->Act;
        }
    }
    else{
        DLError();
    }
}

void DLPreInsert (tDLList *L, int val) {
/*
** Vloží prvek před aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/
    tDLElemPtr help = malloc(sizeof(struct tDLElem));

    if (help != NULL){                      //když e dostatek místta v paměti
        if (L->Act != NULL){                //a když je seznam aktivní,
            help->data = val;               //vloží prvek help před aktivní prvek
            L->Act->lptr->rptr = help;      //a vhodně propojí ukazatele
            help->lptr = L->Act->lptr;
            help->rptr = L->Act;
            L->Act->lptr = help;
        }
    }
    else{
        DLError();
    }
}

void DLCopy (tDLList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu aktivního prvku seznamu L.
** Pokud seznam L není aktivní, volá funkci DLError ().
**/
		
	if(L->Act != NULL){         //když je seznam aktivní,
        *val = L->Act->data;    //vrátí hodnotu aktivního prvku přes val
    }
    else {
        DLError();
    }
}

void DLActualize (tDLList *L, int val) {
/*
** Přepíše obsah aktivního prvku seznamu L.
** Pokud seznam L není aktivní, nedělá nic.
**/
	if (L->Act != NULL){        //když je seznam aktivní,
        L->Act->data = val;     //přepíše hodnotu aktivního prvku
    }
}

void DLSucc (tDLList *L) {
/*
** Posune aktivitu na následující prvek seznamu L.
** Není-li seznam aktivní, nedělá nic.
** Všimněte si, že při aktivitě na posledním prvku se seznam stane neaktivním.
**/
	if (L->Act != NULL){        //posune aktivitu na další prvek seznamu
        L->Act = L->Act->rptr;
    }
}


void DLPred (tDLList *L) {
/*
** Posune aktivitu na předchozí prvek seznamu L.
** Není-li seznam aktivní, nedělá nic.
** Všimněte si, že při aktivitě na prvním prvku se seznam stane neaktivním.
**/
	if (L->Act != NULL){        //posune aktivitu na předchozí prvek seznamu
        L->Act = L->Act->lptr;
    }
}

int DLActive (tDLList *L) {
/*
** Je-li seznam L aktivní, vrací nenulovou hodnotu, jinak vrací 0.
** Funkci je vhodné implementovat jedním příkazem return.
**/
	return (L->Act != NULL);        //test aktivity seznamu -
}                                   //je-li seznam aktivní, vrací nenulovou hodnotu

/* Konec c206.c*/
