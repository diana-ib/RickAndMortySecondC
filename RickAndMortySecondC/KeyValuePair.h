//
// Created by ise on 12/20/22.
//
#include "Defs.h"
#ifndef GENERICADT_KEYVALUEPAIR_H
#define GENERICADT_KEYVALUEPAIR_H
//pointer to struct Key Value Pair
typedef struct KeyValuePair_s *keyValPair;
//create Key Value Pair ,return pair* 
keyValPair createKeyValuePair(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey,Element key,Element val);
//destroing the Key Value Pair and return success or failure
status destroyKeyValuePair(keyValPair kv);
//display the Value Pair and return success or failure
status displayValue(keyValPair kv);
//display the key Pair and return success or failure
status displayKey(keyValPair kv);
//receiving pair and geting the value 
Element getValue(keyValPair kv);
//receiving pair and geting the key 
Element getKey(keyValPair kv);
//checking if the tow elements are equals and return true, if they are not return false 
bool isEqualKey(keyValPair kv,Element key);


#endif //GENERICADT_KEYVALUEPAIR_H
