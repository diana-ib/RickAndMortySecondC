//
// Created by ise on 12/20/22.
//
#include "Defs.h"
#include "LinkedList.h"
#ifndef GENERICADT_MULTIVALUEHASHTABLE_H
#define GENERICADT_MULTIVALUEHASHTABLE_H
//pointer to struct multiValHashTable
typedef struct multiValHashTable *multiH;
//create MultiValueHashTable
multiH createMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey,EqualFunction equalValue, TransformIntoNumberFunction transformIntoNumber, int hashNumber);
//destroy the MultiHashTable and returning success or failure
status destroyMultiValueHashTable(multiH m);
//receving MultiHashTable,key,value and adding a list to MultiHashTable,returning success or failure
status  addToMultiValueHashTable(multiH m,Element key,Element val);
//receiving MultiHashTable,key if the search find the list by Key
linkedList lookupInMultiValueHashTable(multiH m,Element key);
//receving MultiHashTable,key,value and removing a jerry from MultiHashTable,returning success or failure
status removeFromMultiValueHashTable(multiH m,Element key,Element val);
//receving MultiValueHashTable and key , print it and returning 
status  displayMultiValueHashElementsByKey(multiH m, Element key);
#endif //GENERICADT_MULTIVALUEHASHTABLE_H
