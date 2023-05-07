//
// Created by ise on 12/20/22.
//

#include "KeyValuePair.h"
struct KeyValuePair_s {
    Element key;
    Element value;
    CopyFunction copyKey;
    FreeFunction freeKey;
    PrintFunction printKey;
    EqualFunction equalKey;
    CopyFunction copyValue;
    FreeFunction freeValue;
    PrintFunction printValue;

};
keyValPair createKeyValuePair(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey,Element key,Element val){
    if(copyKey==NULL ||freeKey==NULL|| printKey==NULL|| copyValue==NULL ||freeValue==NULL|| printValue==NULL||equalKey==NULL)
        return NULL;
    keyValPair newKV=(keyValPair) malloc(sizeof (struct KeyValuePair_s));
    if(newKV==NULL)
        return NULL;
    newKV->copyKey=copyKey;
    newKV->copyValue=copyValue;
    newKV->freeKey=freeKey;
    newKV->freeValue=freeValue;
    newKV->printKey=printKey;
    newKV->printValue=printValue;
    newKV->equalKey=equalKey;
    newKV->key=copyKey(key);
    newKV->value=copyValue(val);
    return newKV;
}
status destroyKeyValuePair(keyValPair kv){
    if(kv ==NULL)
       return failure;
    kv->freeValue(kv->value);
    kv->freeKey(kv->key);
    free(kv);
    return success;

}
status displayValue(keyValPair kv){
    if(kv==NULL)
        return failure;
    kv->printValue(kv->value);
    return success;

}
status displayKey(keyValPair kv){
    if(kv==NULL)
        return failure;
    kv->printKey(kv->key);
    return success;
}
Element getValue(keyValPair kv){
    if(kv==NULL)
        return NULL;
    return kv->value;

}
Element getKey(keyValPair kv){
    if(kv==NULL)
        return NULL;
    return kv->key;

}
bool isEqualKey(keyValPair kv,Element key){
    if(kv==NULL|| key==NULL)
        return false;
    if(kv->equalKey(kv->key,key))
        return true;
    return false;

}

