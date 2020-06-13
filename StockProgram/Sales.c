#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Inventory.h"
#include "StockItem.h"
#include "Sales.h"

Sale* saleHead;
Sale* saleTail;
int saleListLength = 0;

Sale* SaleConstructor(char* date, char* stockCode, int amount){
    Sale* s = (Sale*)malloc(sizeof(Sale));
    s->date = date;
    s->stockCode = stockCode;
    s->amount = amount;
    return s;
}

void printSale(Sale* sale){
    char* date = sale->date;
    char* sCode = sale->stockCode;
    int amount = sale->amount;
    printf("date=%s; stockCode=%s; amount=%d \n", date, sCode, amount);
}

void printLinkedList(){
    Sale* saleToPrint = saleHead;
    //printSale(saleToPrint);
    for (int n=0; n<saleListLength; n++){
        printSale(saleToPrint);
        saleToPrint = saleToPrint->next;
    }
}


void addSale(Sale* newSale){    
    if(saleListLength == 0){
        saleHead = newSale;
        saleTail = newSale;
    }else{
        saleTail->next = newSale;
    }
    saleListLength += 1;
    saleTail = newSale;
}



void removeSale(Sale* toDelete){
    Sale* currentSale = saleHead;
    Sale* previousToCurrentSale;
    for(int n=0; n<saleListLength; n++){
        if(compareSale(toDelete, currentSale) == 1){
            saleListLength -= 1;
            if(currentSale == saleHead){
                saleHead = saleHead->next;                        
            }else if (currentSale == saleTail){
                saleTail = previousToCurrentSale;
                free(currentSale);
            }else{
                previousToCurrentSale->next = currentSale->next;
                free(currentSale);  
            }
        }
        previousToCurrentSale  = currentSale;
        currentSale = currentSale->next;
    }
}




int compareSale(Sale* sale1, Sale* sale2){
    int equal = 0;
    if(strcmp(sale1->date, sale2->date) == 0 && 
            strcmp(sale1->stockCode, sale2->stockCode) == 0 && 
            (sale1->amount == sale2->amount)){
        equal = 1;
    }
    return equal;
}

void processSales(){
    Sale* saleToProcess = saleHead;
    
    for (int n=0; n<saleListLength; n++){
        Node* nodeStockItem = invHead;
        for (int z=0; z<invListLength; z++){
            if(strcmp(saleToProcess->stockCode, nodeStockItem->stockItem->itemCode) == 0){
                if(saleToProcess->amount > nodeStockItem->stockItem->stockCount){
                    fprintf(stderr, "Order on date %s for item %s cannot be completed (%d>%d)\n", saleToProcess->date, saleToProcess->stockCode, saleToProcess->amount, nodeStockItem->stockItem->stockCount);
                    removeSale(saleToProcess);
                    break;
                }else{
                    nodeStockItem->stockItem->stockCount -= saleToProcess->amount;
                    break;
                }
            }
            nodeStockItem = nodeStockItem->next;
        }
        saleToProcess = saleToProcess->next;
    }
}



void loadSales(){
    FILE *salesFile = fopen("Sales.txt", "r");
    rewind(salesFile);
    clearerr(salesFile);
    
    char* lineP = NULL;
    size_t len;

    Sale *currentSale;
    char* date;
    char* stockCode;
    int amount;
    
    while (getline(&lineP, &len, salesFile) != -1){
        char* currentLine = malloc(strlen(lineP)+1);
        strncpy(currentLine, lineP, strlen(lineP)+1);

        date = strtok(currentLine, ", ");
        stockCode = strtok(NULL, ", ");
        amount = atoi(strtok(NULL, ","));
        
        currentSale = SaleConstructor(date, stockCode, amount);
        addSale(currentSale);
    }
    fclose(salesFile); 
}