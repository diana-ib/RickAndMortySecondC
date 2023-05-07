//
// Created by ise on 12/20/22.
//

#include "MultiValueHashTable.h"
#include "HashTable.h"
struct multiValHashTable{
    CopyFunction copyKeymh;
    FreeFunction freeKeymh;
    PrintFunction printKeymh;
    EqualFunction equalKeymh;
    CopyFunction copyValuemh;
    FreeFunction freeValuemh;
    PrintFunction printValuemh;
    TransformIntoNumberFunction transformIntoNumbermh;
    hashTable hTable;
    int multiSize;
    EqualFunction equalValue;

};
linkedList copyLinkedList(linkedList l){
    if(l==NULL)
        return NULL;
    return l;
}

multiH createMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey,EqualFunction  equalValue, TransformIntoNumberFunction transformIntoNumber, int hashNumber){
    if(copyKey==NULL||freeKey==NULL||printKey==NULL||copyValue==NULL||freeValue==NULL||printValue==NULL||equalKey==NULL||transformIntoNumber==NULL){
        return NULL;
    }
    multiH newMultiHT=(multiH) malloc(sizeof (struct multiValHashTable));
    if(newMultiHT==NULL)
        return NULL;
    newMultiHT->copyKeymh=copyKey;
    newMultiHT->freeKeymh=freeKey;
    newMultiHT->printKeymh=printKey;
    newMultiHT->equalKeymh=equalKey;
    newMultiHT->copyValuemh=copyValue;
    newMultiHT->freeValuemh=freeValue;
    newMultiHT->printValuemh=printValue;
    newMultiHT->transformIntoNumbermh=transformIntoNumber;
    newMultiHT->multiSize=hashNumber;
    newMultiHT->equalValue=equalValue;
    newMultiHT->hTable= createHashTable(copyKey, freeKey, printKey, (CopyFunction)copyLinkedList, (FreeFunction) destroyList, (PrintFunction) displayList, equalKey, transformIntoNumber, hashNumber);
    if(newMultiHT->hTable==NULL){
        free(newMultiHT);
        return NULL;
    }

    return newMultiHT;
}
//bool compareList(linkedList l,Element key){
//    return l==key;
//}
status destroyMultiValueHashTable(multiH m){
    if(m==NULL)
        return failure;
    destroyHashTable(m->hTable);
    free(m);
    return success;

}
status  addToMultiValueHashTable(multiH m,Element key,Element val){

    if(m==NULL||key==NULL||val==NULL)
        return failure;
    if( lookupInHashTable(m->hTable,key)==NULL){
        linkedList  list;
        list= createLinkedList(m->copyValuemh,m->freeValuemh,m->printValuemh,m->equalValue);
        if(list==NULL)
            return failure;
        appendNode(list, val);
        addToHashTable(m->hTable, key,(Element )list);
    }

    else
    {
        linkedList list =lookupInHashTable(m->hTable,key);
        appendNode(list, val);
    }
    return success;


}
linkedList lookupInMultiValueHashTable(multiH m,Element key){
    if(m==NULL||key==NULL)
        return NULL;

    Element l=lookupInHashTable(m->hTable,key);
    if(l==NULL)
        return NULL;
    return (l);


}
status removeFromMultiValueHashTable(multiH m,Element key,Element val){
    if(m==NULL||key==NULL||val==NULL||lookupInMultiValueHashTable(m,key)==NULL)
        return failure;
    else{
        if(getLengthList(lookupInMultiValueHashTable(m,key))==1)
            removeFromHashTable(m->hTable,key);
        else{
            deleteNode(lookupInMultiValueHashTable(m,key),val);
        }
        return success;
    }

}

status  displayMultiValueHashElementsByKey(multiH m, Element key){
    if(m==NULL||key==NULL||lookupInMultiValueHashTable(m,key)==NULL){
        return failure;
    }
    displayList(lookupInMultiValueHashTable(m,key));
    return success;

}