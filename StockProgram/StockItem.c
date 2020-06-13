#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Inventory.h"
#include "Sales.h"
#include "StockItem.h"



StockItem* StockItemConstructor(char* itemName, char* itemCode, int price, int stockCount, char* otherInfo){
    StockItem* stockItem = (StockItem*)malloc(sizeof(StockItem));
    stockItem->itemCode = itemCode;
    stockItem->itemName = itemName;
    stockItem->otherInfo = otherInfo;
    stockItem->price = price;
    stockItem->stockCount = stockCount;
    return stockItem;
}

void printStockItem(StockItem* item){
    //Helpful for debugging, also called when printing the entire linked list.
    char* itemName = item->itemName;
    char* itemCode = item->itemCode;
    char* otherInfo = item->otherInfo;
    int price = item->price;
    int pounds = price/100;
    int pence = price%100;
    int stockCount = item->stockCount;
    printf("Name: %s, Code:%s, Price:£%d.%02d, Stock Count:%d, Other:%s", itemName, itemCode, pounds, pence, stockCount, otherInfo);
}


void loadStockItems(){
    FILE *inventory = fopen("testProgram.txt", "r");
    rewind(inventory);
    //rewind the cursor to the start of file.
    
    char* lineP = NULL;
    //pointer to the beginning of the line read.
    size_t len;
    
    StockItem *currentStock;
    char* itemName;
    char* itemCode;
    int price;
    int stockCount;
    char* otherInfo;
    
    
    while (getline(&lineP, &len, inventory) != -1){
        char* currentLine = malloc(strlen(lineP)+1);
        strncpy(currentLine, lineP, strlen(lineP)+1);
        //copy line to a new part in memory, otherwise it will get overwritten...
        //...when the next line is read.        
        
        itemName = strtok(currentLine, ", ");
        //using strtok() to break the line into a series of tokens with delimeters.
        //when using strtok() with NULL as the first parameter, it finds the...
        //...next token in that line.
        
        itemCode = strtok(NULL, ", ");
        stockCount = atoi(strtok(NULL, ", "));
        price = atoi(strtok(NULL, ", "));
        //atoi() is used to cast alhpa characters to integers.
        otherInfo = strtok(NULL, ", ");
        if(otherInfo == NULL){
            otherInfo = "No info given.\n";
        }
        
        currentStock = StockItemConstructor(itemName, itemCode, price, stockCount, otherInfo);
        addNode(currentStock);
        //create stock item, and add it to the linked list.
    }
    fclose(inventory);
    //printStockItem(currentStock);
}