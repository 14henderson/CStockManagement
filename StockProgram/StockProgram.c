#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Sales.h"
#include "StockItem.h"
#include "Inventory.h"


/*
 * 
 */
int main(int argc, char** argv) { 
    void greatestSalesVolume();
    
    loadSales();
    loadStockItems();
    //processSales();
    
    //printLinkedList();
    //greatestSalesVolume();
    //sortBy();
    //printInventoryList();
    
    //getNPNTransistors();
    
    
    
    
    
    
    return (EXIT_SUCCESS);
}



void greatestSalesVolume(){
    char* day = saleHead->date;
    Sale* currentSale = saleHead;
    
    int salesPerDay = 0;
    int pencePerDay = 0;
    
    int maxSalesPD = 0;
    int maxPencePD = 0;
    char* maxDay = "";

    
    for(int n=0; n<saleListLength; n++){
        if(strcmp(currentSale->date, day) == 0){
            salesPerDay += currentSale->amount;
            pencePerDay += (getStockPrice(currentSale->stockCode))*currentSale->amount;
        }else{
            if(salesPerDay > maxSalesPD){
                maxSalesPD = salesPerDay;
                maxPencePD = pencePerDay;
                maxDay = day;
            }
            
            salesPerDay = currentSale->amount;
            pencePerDay = getStockPrice(currentSale->stockCode);
            
            day = currentSale->date;
        }
        currentSale = currentSale->next;
    }
    printf("Sales:%d, Pence Made:%d p, Date:%s\n", maxSalesPD, maxPencePD, maxDay);
}
