#ifndef STOCKITEM_H
#define STOCKITEM_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct StockItemStruct
{
    char* itemName;
    char* itemCode;
    int price;
    int stockCount;
    char* otherInfo;
}
StockItem;

void loadStockItems();
void printStockItem(StockItem* item);
//size_t getline(char **lineptr, size_t *n, FILE *stream);


#ifdef __cplusplus
}
#endif

#endif /* STOCKITEM_H */

