#ifndef INTENTORY_H
#define INTENTORY_H

#ifdef __cplusplus
extern "C" {
#endif
#include "StockItem.h"
//must include StockItem.h as InventoryNode Structure...
//...includes Structure from StockItem.
    
//All functions and variables defined here are treated...
//as global, and can be called and referenced from other...
//... .c files.    
    
typedef struct InventoryNode
{
    StockItem* stockItem;
    struct InventoryNode* next;
}Node;

Node* invHead;
Node* invTail;
int invListLength;

void addNode(StockItem* stockItem);
void printInventoryList();
int removeNode(char* itemCode);
void sortBy();
int getStockPrice(char* itemCodeQ);
int getNPNTransistors();

#ifdef __cplusplus
}
#endif

#endif /* INTENTORY_H */

