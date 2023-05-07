//
// Created by ise on 12/20/22.
//

#include "LinkedList.h"

struct Node_s{
    struct Node_s* next;
    Element element;

};
struct linkedList_s{
    CopyFunction copyE;
    FreeFunction freeE;
    PrintFunction printE;
    EqualFunction equalE;
    node head;
    node tail;
    int length;

};
node createNode(Element element) {
    node newnode = (node)malloc(sizeof(struct Node_s));
    if (newnode == NULL) {
        return NULL;
    }
    newnode->element = element;
    newnode->next = NULL;
    return newnode;
}
linkedList createLinkedList(CopyFunction copyEle, FreeFunction freeEle, PrintFunction printEle, EqualFunction equalEle) {
    if(copyEle ==NULL|| freeEle==NULL|| printEle==NULL|| equalEle==NULL)
        return NULL;
    linkedList newList=(linkedList) malloc(sizeof (struct linkedList_s));
    if(newList==NULL){
        return NULL;
    }
    newList->copyE=copyEle;
    newList->equalE=equalEle;
    newList->freeE=freeEle;
    newList->printE=printEle;
    newList->head=NULL;
    newList->tail=NULL;
    newList->length=0;
    return newList;
}
status destroyList(linkedList l){
    if(l==NULL)
        return failure;
    node h=l->head;
    node next;
    for(int i=0;i< l->length;i++){
        l->freeE(h->element);
        next=h->next;
        free(h);
        h=next;
    }
    free(l);
    return success;
}
status appendNode(linkedList l, Element e){
    if(l==NULL || e==NULL)
        return failure;
    if(l->head==NULL){
        node newNode= createNode(e);
        if(newNode==NULL){
            return failure;
        }
        newNode->element=l->copyE(e);
        l->head=newNode;
        l->head->next=NULL;
        l->tail=l->head;

    }
    else{
        node newNode = createNode(e);
        if(newNode==NULL){
            return failure;
        }
        newNode->element= l->copyE(e);
        l->tail->next=newNode;
        l->tail=newNode;
        l->tail->next=NULL;
    }
    l->length++;
    return success;
}
status deleteNode(linkedList l, Element e){
    if(l==NULL|| e==NULL )
        return failure;
    node curr=l->head;
    node prev;
    node temp=curr->next;
    //delete head of linked list

    if(l->equalE(curr->element,e)==true){
        if(l->length==1){
            l->freeE(curr->element);
            free(curr);
            l->head=NULL;
            l->tail=NULL;
            l->length=0;
            return success;
        }
        l->freeE(curr->element);
        free(curr);
        curr=temp;
        l->head=temp;
        l->length--;
        return success;
    }
    prev=curr;
    curr=curr->next;
    //middle
    for(int i=1;i<l->length-1;i++){
        if(l->equalE(curr->element,e)==true){
            prev->next=curr->next;
            l->freeE(curr->element);
            curr->element=NULL;
            free(curr);
            l->length--;
            return success;
        }
        prev=curr;
        curr=curr->next;
    }
    // delete the tail of linked list
    if(l->equalE(curr->element,e)==true){
        l->freeE(curr->element);
        free(curr);
        l->tail=prev;
        prev->next=NULL;
        l->length--;
        return success;
    }

    return failure;
}
status displayList(linkedList l){
    if(l==NULL)
        return failure;
    node curr=l->head;
    while (curr!=NULL){
        l->printE(curr->element);
        curr=curr->next;
    }
    return success;
}
Element getDataByIndex(linkedList l, int i){
    if(l==NULL|| i>l->length)
        return NULL;
    int num=1;
    node curr=l->head;
    while(num!=i){
        curr=curr->next;
        num++;
    }
    return(curr->element);

}
int getLengthList(linkedList l){
    return l->length;
}
Element searchByKeyInList(linkedList l,Element e){
    if(l==NULL|| e==NULL||l->length==0)
        return NULL;
    node curr=l->head;
    for (int i=0;i< l->length;i++){
        if(l->equalE(curr->element,e)==true){
            return curr->element;
        }
        else
        {
            curr=curr->next;
        }
    }
    return NULL;

}
