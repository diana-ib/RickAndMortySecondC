//
// Created by ise on 12/20/22.
//
#include "KeyValuePair.h"
#include "LinkedList.h"
#include "HashTable.h"
struct hashTable_s {
    CopyFunction copyKeyh;
    FreeFunction freeKeyh;
    PrintFunction printKeyh;
    EqualFunction equalKeyh;
    CopyFunction copyValueh;
    FreeFunction freeValueh;
    PrintFunction printValueh;
    TransformIntoNumberFunction transformIntoNumberh;
    int size;
    linkedList* list;
};
bool equalkeyvalPair (Element kv, Element key){
    if(kv==NULL||key==NULL)
        return false;
    return (isEqualKey((keyValPair )kv,key));

}

Element copyKeyValPair(Element kv){
    if(kv==NULL)
        return NULL;
    return kv;
}

status printKeyValPair(Element kv){
    if(kv==NULL)
        return failure;
    displayKey((keyValPair )kv);
    displayValue((keyValPair)kv);
    return success;

}

int elNUM(hashTable h, Element key){
    int x=h->transformIntoNumberh(key);
    int curr=x%(h->size);
    return (curr);
}

hashTable createHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey, TransformIntoNumberFunction transformIntoNumber, int hashNumber){
    if(copyKey==NULL||freeKey==NULL||printKey==NULL||copyValue==NULL||freeValue==NULL||printValue==NULL||equalKey==NULL||transformIntoNumber==NULL)
        return NULL;
    hashTable newHash=(hashTable)malloc(sizeof (struct hashTable_s));
    if(newHash==NULL)
        return NULL;
    newHash->copyKeyh=copyKey;
    newHash->freeKeyh=freeKey;
    newHash->printKeyh=printKey;
    newHash->equalKeyh=equalKey;
    newHash->copyValueh=copyValue;
    newHash->freeValueh=freeValue;
    newHash->printValueh=printValue;
    newHash->size=hashNumber;
    newHash->transformIntoNumberh=transformIntoNumber;
    newHash->list=(linkedList*)malloc((sizeof (linkedList))*hashNumber);
    if(newHash->list==NULL){
        free(newHash);
        return NULL;
    }
    for(int i=0;i<hashNumber;i++ ){
        newHash->list[i]= createLinkedList((CopyFunction)copyKeyValPair , (FreeFunction)destroyKeyValuePair , (PrintFunction) displayValue, (EqualFunction)isEqualKey);
        if(newHash->list[i]==NULL){
            for(int j=0;j<i;j++){
                destroyList(newHash->list[j]);
            }
            free(newHash->list);
            free(newHash);
            return NULL;
        }
    }

    return newHash;

}
status destroyHashTable(hashTable h){
    if(h==NULL)
        return failure;
    for(int i=0;i<h->size;i++){
        destroyList(h->list[i]);
    }
    free(h->list);
    free(h);
    return success;

}
status addToHashTable(hashTable h, Element key,Element value){
    if(h==NULL|| key==NULL|| value==NULL)
        return failure;
    keyValPair newPair=createKeyValuePair(h->copyKeyh,h->freeKeyh,h->printKeyh, h->copyValueh, h->freeValueh, h->printValueh, h->equalKeyh,key,value);
    if(newPair==NULL){
        return failure;
    }
    int index= elNUM( h, key);
    if(h->list[index]==NULL){
        linkedList list= createLinkedList((CopyFunction) copyKeyValPair, (FreeFunction) destroyKeyValuePair, (PrintFunction) printKeyValPair, (EqualFunction)equalkeyvalPair);
        if(list==NULL){
            destroyKeyValuePair(newPair);
            return failure;
        }
        h->list[index]=list;

        if(appendNode(h->list[index],newPair)==failure) {
            destroyKeyValuePair(newPair);
            destroyList(list);
            return failure;
        }
    }
    else
    {
        if(appendNode(h->list[index],newPair)==failure) {
            destroyKeyValuePair(newPair);
            return failure;
        }
    }

    return (success);
}
Element lookupInHashTable(hashTable h, Element key){
    if(h==NULL||key==NULL)
        return NULL;
    int x= elNUM(h,key);
    Element keyValPair1=searchByKeyInList(h->list[x],key);
    if(keyValPair1!=NULL){
        return getValue(keyValPair1);
    }
    return NULL;

}
status removeFromHashTable(hashTable h, Element key){
    if(h==NULL||key==NULL)
        return failure;
    return (deleteNode(h->list[elNUM(h, key)], key));
}
status displayHashElements(hashTable h){
    if(h==NULL)
        return failure;
    for(int i=0;i<h->size;i++){
        displayList(h->list[i]);

    }
    return success;

}


