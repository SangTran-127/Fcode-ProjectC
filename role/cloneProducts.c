#include <stdio.h>
typedef struct
{
    int id;
    char* name;
    int supplier;
    int price;
    double discount;
    int quantity;
} Product;

Product databaseProducts[500];
int numberOfProducts = 0;

void cloneProducts(){
    numberOfProducts = 1;
    FILE *fp = fopen("products.csv", "r");
    char* str = malloc(1000);
    while (fgets(str, 1000, fp) != NULL)
    {
        printf("\n================");
        databaseProducts[numberOfProducts].id = 0;
        databaseProducts[numberOfProducts].supplier = 0;
        databaseProducts[numberOfProducts].price = 0;
        databaseProducts[numberOfProducts].discount = 0;
        databaseProducts[numberOfProducts].quantity = 0;
        int pos = 0;
        while (str[pos] != ',')
        {
            int tmp = (int)str[pos] - '0';
            databaseProducts[numberOfProducts].id = databaseProducts[numberOfProducts].id * 10 + tmp;
            pos++;
        }
        printf("\n%d", databaseProducts[numberOfProducts].id);
        pos++;
        strcpy(databaseProducts[numberOfProducts].name, "");
        while (str[pos] != ',')
        {
            int tmp = (int)str[pos];
            strcat(databaseProducts[numberOfProducts].name, &tmp);
            pos++;
        }
        printf("\n%s", databaseProducts[numberOfProducts].name);
        pos++;
        while (str[pos] != ',')
        {
            int tmp = (int)str[pos] - '0';
            databaseProducts[numberOfProducts].supplier = databaseProducts[numberOfProducts].supplier * 10 + tmp;
            pos++;
        }
        printf("\n%d", databaseProducts[numberOfProducts].supplier);
        pos++;
        while (str[pos] != ',')
        {
            int tmp = (int)str[pos] - '0';
            databaseProducts[numberOfProducts].price = databaseProducts[numberOfProducts].price * 10 + tmp;
            pos++;
        }
        printf("\n%d", databaseProducts[numberOfProducts].price);
        pos++;
        while (str[pos] != ',')
        {
            int tmp = (int)str[pos] - '0';
            databaseProducts[numberOfProducts].discount = databaseProducts[numberOfProducts].discount * 10 + tmp;
            pos++;
        }
        printf("\n%d", databaseProducts[numberOfProducts].discount);
        pos++;
        while (str[pos] != 0)
        {
            int tmp = (int)str[pos] - '0';
            databaseProducts[numberOfProducts].quantity = databaseProducts[numberOfProducts].quantity * 10 + tmp;
            pos++;
        }
        pos++;
        printf("\n%d", databaseProducts[numberOfProducts].quantity);
        numberOfProducts++;
    }
    fclose(fp);
}

int main(){
    for(int i  = 0; i < 500; i++){
        databaseProducts[i].name = malloc(200);
    }
    cloneProducts();
    return 0;
}
