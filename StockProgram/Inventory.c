#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "StockItem.h"
#include "Sales.h"
#include "Inventory.h"

//Head and tail of linked list.
Node* invHead;
Node* invTail;
int invListLength = 0;

void addNode(StockItem* stockItem){
    Node* node = (Node*)malloc(sizeof(Node));
    //Use malloc to ensure the memory address isn't overwritten or collected
    //by the garbage collection.
    node->stockItem = stockItem;
    if (invListLength == 0){
        invHead = node;
        invTail = node;
    }else{
        invTail->next = node;
        node->next = NULL;
    }
    invListLength += 1;
    invTail = node;
}



int removeNode(char* itemCode){
    //removed item from linked list, and frees memory.
    Node* currentNode = invHead;
    
    int found = 0;
    Node* temp;
    Node* previousToCurrentNode;
    for(int n=0; n<invListLength; n++){
        if(strcmp(itemCode, currentNode->stockItem->itemCode) == 0){
            //if currentNode is the node that needs to be deleted
            found = 1;
            invListLength -= 1;
            if(currentNode == invHead){
                invHead = invHead->next;
                free(currentNode->stockItem);
                free(currentNode);
                //using free to indicate that these bits of memory are no...
                //...longer in use, and can be overwritten.
            }else if(currentNode == invTail){
                temp = invTail;
                invTail = previousToCurrentNode;
                previousToCurrentNode->next = NULL;
                free(temp);
            }else{
                previousToCurrentNode->next = currentNode->next;
                free(currentNode);
            }
        }
        previousToCurrentNode = currentNode;
        currentNode = currentNode->next;
    }
    //return 1 for function success, 0 for failure.
    if(found == 1){return 0;}else{return 1;}
}


int getStockPrice(char* itemCodeQ){
    //Performs a linear search through the linked list, and returns price.
    Node* currentNode = invHead;
    for (int n=0; n<invListLength; n++){
        if(strcmp(currentNode->stockItem->itemCode, itemCodeQ) == 0){
            return (currentNode->stockItem->price);
        }else{
            currentNode = currentNode->next;
        }
    }
}



int getNPNTransistors(){
    Node* currentNode = invHead;
    int totalTransistors = 0;
    for (int n=0; n<invListLength; n++){
        if(strcmp(currentNode->stockItem->otherInfo, "NPN") == 0){
            //using cmpstr() to compare strings, as you would otherwise be comparing memory addresses.
            totalTransistors += currentNode->stockItem->stockCount;
        }
        currentNode = currentNode->next;
    }
    printf("There are %d NPN transistors left in store.\n", totalTransistors);
}



void sortBy(){
    //Adapted bubble sort algorithm.
    //Original algorithm provided by Gavin
   if (invHead != invTail){
      int sorted;
      do{
         sorted = 1; 
         for (Node* node=invHead; node->next!=NULL; node=node->next){
            if (node->stockItem->price < node->next->stockItem->price){
               StockItem* temp = node->stockItem;
               node->stockItem = node->next->stockItem;
               node->next->stockItem = temp;
               sorted = 0;
            }
         }
      }
      while (!sorted);
   }
}



void printInventoryList(){
    //Useful for debugging
    Node* nodeToPrint = invHead;
    while (nodeToPrint != invTail){
        printStockItem(nodeToPrint->stockItem);
        nodeToPrint = nodeToPrint->next;
    }
    printStockItem(invTail->stockItem);
}