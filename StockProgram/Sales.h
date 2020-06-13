#ifndef SALES_H
#define SALES_H

#ifdef __cplusplus
extern "C" {
#endif
    

typedef struct SaleStruct
{
    char* date;
    char* stockCode;
    int   amount;
    
    struct SaleStruct* next;
}Sale;

Sale* saleHead;
Sale* saleTail;
int saleListLength;

void loadSales();
Sale* SaleConstructor(char* date, char* stockCode, int amount);
int compareSale(Sale* sale1, Sale* sale2);
void printLinkedList();
void processSales();
void removeSale(Sale* toDelete);

#ifdef __cplusplus
}
#endif

#endif /* SALES_H */

