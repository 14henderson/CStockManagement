#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "StockItem.h"
#include "Sales.h"
#include "Inventory.h"


Node* invHead;
Node* invTail;
int invListLength = 0;

typedef enum {
    NAME,
    CODE,
    PRICE,
    STOCK
} FIELD;


void addNode(StockItem* stockItem){
    Node* node = (Node*)malloc(sizeof(Node));
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



void removeNode(char* itemCode){
    Node* currentNode = invHead;
    Node* previousToCurrentNode;
    for(int n=0; n<invListLength; n++){
        if(strcmp(itemCode, currentNode->stockItem->itemCode) == 0){
            invListLength -= 1;
            if(currentNode == invHead){
                invHead = invHead->next;
            }else if(currentNode == invTail){
                invTail = previousToCurrentNode;
                previousToCurrentNode->next = NULL;
            }else{
                previousToCurrentNode->next = currentNode->next;
            }
        }
        previousToCurrentNode = currentNode;
        currentNode = currentNode->next;
    }
}


int getStockPrice(char* itemCodeQ){
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
            totalTransistors += currentNode->stockItem->stockCount;
        }
        currentNode = currentNode->next;
    }
    printf("There are %d NPN transistors left in store.\n", totalTransistors);
}



void sortBy(){
   if (invHead != invTail){
      int sorted;
      do{
         sorted = 1; 
         for (Node* node=invHead; node->next!=NULL; node=node->next){
            if (node->stockItem->price < node->next->stockItem->price){
               int temp = node->stockItem;
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

void getTotalResistance(){
    Node* currentNode = invHead;
    char resistanceString[4];
    
    for (int n=0; n<invListLength; n++){
        if(strcmp(currentNode->stockItem->itemName, "resistor") == 0){
            strncpy(resistanceString, currentNode->stockItem->otherInfo, 4);
            printf("%s", resistanceString);//[0], resistanceString[1], resistanceString[2]);
            //char resistanceString[] = currentNode->stockItem->otherInfo;
            /*
            
            int multiplier = 1;
            for (int n=0; n<strlen(resistanceString);n++){
                
                if(strcmp(resistanceString[n], "K")){
                    multiplier = 1000;
                }else if (strcmp(resistanceString[n], "M" == 0)){
                    multiplier = 1000000;
                }
                resistanceString[n] = ".";
            }
            printf("%s        %d", resistanceString, multiplier);
             */
        }
             
        
    }
}
