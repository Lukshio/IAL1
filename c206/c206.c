/* ******************************* c206.c *********************************** */
/*  Předmět: Algoritmy (IAL) - FIT VUT v Brně                                 */
/*  Úkol: c206 - Dvousměrně vázaný lineární seznam                            */
/*  Návrh a referenční implementace: Bohuslav Křena, říjen 2001               */
/*  Vytvořil: Martin Tuček, říjen 2004                                        */
/*  Upravil: Kamil Jeřábek, září 2020                                         */
/*           Daniel Dolejška, září 2021                                       */
/*           Daniel Dolejška, září 2022                                       */
/* ************************************************************************** */
/*
** Implementujte abstraktní datový typ dvousměrně vázaný lineární seznam.
** Užitečným obsahem prvku seznamu je hodnota typu int. Seznam bude jako datová
** abstrakce reprezentován proměnnou typu DLList (DL znamená Doubly-Linked
** a slouží pro odlišení jmen konstant, typů a funkcí od jmen u jednosměrně
** vázaného lineárního seznamu). Definici konstant a typů naleznete
** v hlavičkovém souboru c206.h.
**
** Vaším úkolem je implementovat následující operace, které spolu s výše
** uvedenou datovou částí abstrakce tvoří abstraktní datový typ obousměrně
** vázaný lineární seznam:
**
**      DLL_Init ........... inicializace seznamu před prvním použitím,
**      DLL_Dispose ........ zrušení všech prvků seznamu,
**      DLL_InsertFirst .... vložení prvku na začátek seznamu,
**      DLL_InsertLast ..... vložení prvku na konec seznamu,
**      DLL_First .......... nastavení aktivity na první prvek,
**      DLL_Last ........... nastavení aktivity na poslední prvek,
**      DLL_GetFirst ....... vrací hodnotu prvního prvku,
**      DLL_GetLast ........ vrací hodnotu posledního prvku,
**      DLL_DeleteFirst .... zruší první prvek seznamu,
**      DLL_DeleteLast ..... zruší poslední prvek seznamu,
**      DLL_DeleteAfter .... ruší prvek za aktivním prvkem,
**      DLL_DeleteBefore ... ruší prvek před aktivním prvkem,
**      DLL_InsertAfter .... vloží nový prvek za aktivní prvek seznamu,
**      DLL_InsertBefore ... vloží nový prvek před aktivní prvek seznamu,
**      DLL_GetValue ....... vrací hodnotu aktivního prvku,
**      DLL_SetValue ....... přepíše obsah aktivního prvku novou hodnotou,
**      DLL_Previous ....... posune aktivitu na předchozí prvek seznamu,
**      DLL_Next ........... posune aktivitu na další prvek seznamu,
**      DLL_IsActive ....... zjišťuje aktivitu seznamu.
**
** Při implementaci jednotlivých funkcí nevolejte žádnou z funkcí
** implementovaných v rámci tohoto příkladu, není-li u funkce explicitně
 * uvedeno něco jiného.
**
** Nemusíte ošetřovat situaci, kdy místo legálního ukazatele na seznam
** předá někdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodně komentujte!
**
** Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
** Proto zde používáme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako procedury
** (v jazyce C procedurám odpovídají funkce vracející typ void).
**
**/

#include "c206.h"

int error_flag;
int solved;

/**
 * Vytiskne upozornění na to, že došlo k chybě.
 * Tato funkce bude volána z některých dále implementovaných operací.
 */
void DLL_Error() {
	printf("*ERROR* The program has performed an illegal operation.\n");
	error_flag = TRUE;
}

/**
 * Provede inicializaci seznamu list před jeho prvním použitím (tzn. žádná
 * z následujících funkcí nebude volána nad neinicializovaným seznamem).
 * Tato inicializace se nikdy nebude provádět nad již inicializovaným seznamem,
 * a proto tuto možnost neošetřujte.
 * Vždy předpokládejte, že neinicializované proměnné mají nedefinovanou hodnotu.
 *
 * @param list Ukazatel na strukturu dvousměrně vázaného seznamu
 */
void DLL_Init( DLList *list ) {
    // Inicializace seznamu
    list->firstElement = NULL;
    list->lastElement = NULL;
    list->activeElement = NULL;
}

/**
 * Zruší všechny prvky seznamu list a uvede seznam do stavu, v jakém se nacházel
 * po inicializaci.
 * Rušené prvky seznamu budou korektně uvolněny voláním operace free.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_Dispose( DLList *list ) {
    //TODO tohle jen kopie z C201
    if (list != NULL || list->firstElement != NULL) {
        struct DLLElement *delNode = list->firstElement;
        while (delNode != NULL){
            list->firstElement = delNode->nextElement;
            free(delNode);
            delNode = list->firstElement;
        }
        list->firstElement = NULL;
        list->activeElement = NULL;
    } else {
        return;
    }
}

/**
 * Vloží nový prvek na začátek seznamu list.
 * V případě, že není dostatek paměti pro nový prvek při operaci malloc,
 * volá funkci DLL_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param data Hodnota k vložení na začátek seznamu
 */
void DLL_InsertFirst( DLList *list, int data ) {
    struct DLLElement *newNode = malloc(sizeof (struct DLLElement)); //alokace pameti
    // kontrola jestli se spravne alokovala pamet
    if(newNode == NULL){
        DLL_Error();
        return;
    } else {
        // nastavim newNode jako 1. element, pridam do stavajiciho 1.el newNode jako prev v dalsim kroku prepisu head listu na newNode
        newNode->previousElement = NULL;
        newNode->nextElement = list->firstElement;
        newNode->data = data;
        // kontrola jestli vubec nejaky prvek existuje
        if(list->firstElement != NULL)list->firstElement->previousElement = newNode;
        list->firstElement = newNode;
    }
}

/**
 * Vloží nový prvek na konec seznamu list (symetrická operace k DLL_InsertFirst).
 * V případě, že není dostatek paměti pro nový prvek při operaci malloc,
 * volá funkci DLL_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param data Hodnota k vložení na konec seznamu
 */
void DLL_InsertLast( DLList *list, int data ) {
    struct DLLElement *newNode = malloc(sizeof (struct DLLElement));
    if(newNode == NULL){
        DLL_Error();
        return;
    } else {
        // set newNode
        newNode->nextElement = NULL;
        newNode->previousElement = list->lastElement;
        newNode->data = data;
        //posun na novy konec + kontrola prazneho seznamu
//        if(lastNode == NULL){
//            list->firstElement = newNode;
//        } else {
//            list->lastElement->nextElement = newNode;
//        }
        (list->lastElement == NULL) ? (list->firstElement = newNode) : (list->lastElement->nextElement = newNode);
    }
}

/**
 * Nastaví první prvek seznamu list jako aktivní.
 * Funkci implementujte jako jediný příkaz, aniž byste testovali,
 * zda je seznam list prázdný.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_First( DLList *list ) {
    list->activeElement = list->firstElement;
}

/**
 * Nastaví poslední prvek seznamu list jako aktivní.
 * Funkci implementujte jako jediný příkaz, aniž byste testovali,
 * zda je seznam list prázdný.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_Last( DLList *list ) {
    list->activeElement = list->lastElement;
}

/**
 * Prostřednictvím parametru dataPtr vrátí hodnotu prvního prvku seznamu list.
 * Pokud je seznam list prázdný, volá funkci DLL_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param dataPtr Ukazatel na cílovou proměnnou
 */
void DLL_GetFirst( DLList *list, int *dataPtr ) {
    //kontrola existence, pote pripadne vracim data
    (list == NULL || list->firstElement == NULL || dataPtr == NULL) ? DLL_Error() : (*dataPtr = list->firstElement->data) ;
}

/**
 * Prostřednictvím parametru dataPtr vrátí hodnotu posledního prvku seznamu list.
 * Pokud je seznam list prázdný, volá funkci DLL_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param dataPtr Ukazatel na cílovou proměnnou
 */
void DLL_GetLast( DLList *list, int *dataPtr ) {
    //kontrola existence, pote pripadne vracim data
    (list == NULL || list->lastElement == NULL || dataPtr == NULL) ? DLL_Error() : (*dataPtr = list->lastElement->data) ;
}

/**
 * Zruší první prvek seznamu list.
 * Pokud byl první prvek aktivní, aktivita se ztrácí.
 * Pokud byl seznam list prázdný, nic se neděje.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_DeleteFirst( DLList *list ) {
    if(list->firstElement != NULL && list != NULL){
        // ztrata aktivity pokud je prvek stejny
        if(list->activeElement == list->firstElement) list->activeElement = NULL;

        //pokud ma list 2. prvek, zrusi se jeho pointer na 1. prvek
        struct DLLElement *secondNode = list->firstElement->nextElement;
        if(secondNode != NULL) secondNode = NULL;

        // uvolni pamet po 1. prvku a nastav 2. prvek jako 1.
        free(list->firstElement);
        list->firstElement = secondNode;
    }
}

/**
 * Zruší poslední prvek seznamu list.
 * Pokud byl poslední prvek aktivní, aktivita seznamu se ztrácí.
 * Pokud byl seznam list prázdný, nic se neděje.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_DeleteLast( DLList *list ) {
    if(list->lastElement != NULL && list != NULL){
        // ztrata aktivity pokud je prvek stejny
        if(list->activeElement == list->lastElement) list->activeElement = NULL;

        //pokud ma list predposledni prvek, zrusi se jeho pointer na posledni prvek
        struct DLLElement *prelastNode = list->lastElement->previousElement;
        if(prelastNode != NULL) prelastNode->nextElement = NULL;

        // uvolni pamet po poslednim prvku a nastav predposledni prvek jako posledni
        free(list->lastElement);
        list->lastElement = prelastNode;
    }
}

/**
 * Zruší prvek seznamu list za aktivním prvkem.
 * Pokud je seznam list neaktivní nebo pokud je aktivní prvek
 * posledním prvkem seznamu, nic se neděje.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_DeleteAfter( DLList *list ) {
    //kontrola exitence
    if(list != NULL && list->activeElement != NULL && list->activeElement->nextElement != NULL){
        //ulozim si adresu prvku co budu mazat
        struct DLLElement *delNode = list->activeElement->nextElement;

        // pokud za mazanym prvkem je dalsi, propojim jejich adresy s aktivnim
        if(delNode->nextElement != NULL){
            list->activeElement->nextElement = delNode->nextElement;
            delNode->previousElement = list->activeElement;
        }

        //uvolnim pamet
        free(delNode);
    }
}

/**
 * Zruší prvek před aktivním prvkem seznamu list .
 * Pokud je seznam list neaktivní nebo pokud je aktivní prvek
 * prvním prvkem seznamu, nic se neděje.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_DeleteBefore( DLList *list ) {
    //kontrola existence
    if(list != NULL && list->activeElement != NULL && list->activeElement->nextElement != NULL){
        //ulozim si adresu prvku co budu mazat
        struct DLLElement *delNode = list->activeElement->previousElement;

        // pokud pred mazanym prvkem je dalsi, propojim jejich adresy s aktivnim
        if(delNode->previousElement != NULL){
            list->activeElement->previousElement = delNode->previousElement;
            delNode->nextElement = list->activeElement;
        }

        //uvolnim pamet
        free(delNode);
    }
}

/**
 * Vloží prvek za aktivní prvek seznamu list.
 * Pokud nebyl seznam list aktivní, nic se neděje.
 * V případě, že není dostatek paměti pro nový prvek při operaci malloc,
 * volá funkci DLL_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param data Hodnota k vložení do seznamu za právě aktivní prvek
 */
void DLL_InsertAfter( DLList *list, int data ) {
    //kontrola existence
    if(list != NULL && list->activeElement != NULL){
        // alokace
        struct DLLElement *newNode = malloc(sizeof (struct DLLElement)); //alokace pameti
        // kontrola jestli se spravne alokovala pamet
        if(newNode == NULL){
            DLL_Error();
            return;
        } else {
            //set noveho prvku
            newNode->data = data;
            newNode->nextElement = list->activeElement->nextElement;
            newNode->previousElement = list->activeElement;
            // pokud existuje prvek za aktivnim, posunu pointery
            if(list->activeElement->nextElement != NULL) list->activeElement->nextElement->previousElement = newNode;
            list->activeElement->nextElement = newNode;
        }
    }
}

/**
 * Vloží prvek před aktivní prvek seznamu list.
 * Pokud nebyl seznam list aktivní, nic se neděje.
 * V případě, že není dostatek paměti pro nový prvek při operaci malloc,
 * volá funkci DLL_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param data Hodnota k vložení do seznamu před právě aktivní prvek
 */
void DLL_InsertBefore( DLList *list, int data ) {
    //kontrola existence
    if(list != NULL && list->activeElement != NULL){
        // alokace
        struct DLLElement *newNode = malloc(sizeof (struct DLLElement)); //alokace pameti
        // kontrola jestli se spravne alokovala pamet
        if(newNode == NULL){
            DLL_Error();
            return;
        } else {
            //set noveho prvku
            newNode->data = data;
            newNode->nextElement = list->activeElement;
            newNode->previousElement = list->activeElement->previousElement;
            // pokud existuje prvek za aktivnim, posunu pointery
            if(list->activeElement->previousElement != NULL) list->activeElement->previousElement->nextElement = newNode;
            list->activeElement->previousElement = newNode;
        }
    }}

/**
 * Prostřednictvím parametru dataPtr vrátí hodnotu aktivního prvku seznamu list.
 * Pokud seznam list není aktivní, volá funkci DLL_Error ().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param dataPtr Ukazatel na cílovou proměnnou
 */
void DLL_GetValue( DLList *list, int *dataPtr ) {
    if(list != NULL && list->activeElement != NULL){
        *dataPtr = list->activeElement->data;
    } else {
        DLL_Error();
    }
}

/**
 * Přepíše obsah aktivního prvku seznamu list.
 * Pokud seznam list není aktivní, nedělá nic.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param data Nová hodnota právě aktivního prvku
 */
void DLL_SetValue( DLList *list, int data ) {
    if (list != NULL && list->activeElement != NULL) list->activeElement->data = data;
}

/**
 * Posune aktivitu na následující prvek seznamu list.
 * Není-li seznam aktivní, nedělá nic.
 * Všimněte si, že při aktivitě na posledním prvku se seznam stane neaktivním.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */

//TODO tady to haze double free idk proc
void DLL_Next( DLList *list ) {
    //checck existence
    if (list != NULL && list->activeElement != NULL){
        // pokud za aktivnim neni zadny dalsi prvek, nastavi se aktivita na NULL
        if (list->activeElement->nextElement == NULL){
            list->activeElement = NULL;
        } else {
            list->activeElement = list->activeElement->nextElement;
        }
    } else {
        return;
    }
}


/**
 * Posune aktivitu na předchozí prvek seznamu list.
 * Není-li seznam aktivní, nedělá nic.
 * Všimněte si, že při aktivitě na prvním prvku se seznam stane neaktivním.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_Previous( DLList *list ) {
    //checck existence
    if (list != NULL && list->activeElement != NULL){
        // pokud pred aktivnim neni zadny dalsi prvek, nastavi se aktivita na NULL
        if (list->activeElement->previousElement == NULL){
            list->activeElement = NULL;
        } else {
            list->activeElement = list->activeElement->previousElement;
        }
    } else {
        return;
    }
}

/**
 * Je-li seznam list aktivní, vrací nenulovou hodnotu, jinak vrací 0.
 * Funkci je vhodné implementovat jedním příkazem return.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 *
 * @returns Nenulovou hodnotu v případě aktivity prvku seznamu, jinak nulu
 */
int DLL_IsActive( DLList *list ) {
    return list->activeElement != NULL;
}

/* Konec c206.c */
