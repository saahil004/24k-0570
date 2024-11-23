#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct billItem
{
    char name[20];
    int qty;
};

struct item* getItems();
int logIn();
void showItems(struct item *arr, int size);
int billGeneration();



struct item
{
    char name[20];
    char type[10];
    int qty;
    int price;
};


struct employee
{
    char user[20];
    char pass[20];
};

struct item* getItems() {
    FILE *fi = fopen("items.txt", "r");
    int noOfItems;
    fscanf(fi, "%d", &noOfItems);
    // printf("%d", noOfItems);
    char name[20];
    char type[10];
    int qty;
    int price;
    struct item *items = (struct item*)malloc(noOfItems*sizeof(struct item));
    for (int i = 0; i < noOfItems; i++)
    {
        fscanf(fi, "%19s", name);
        fscanf(fi, "%9s", type);
        fscanf(fi, "%d", &qty);
        fscanf(fi, "%d", &price);
        strcpy(items[i].name, name);
        strcpy(items[i].type, type);
        items[i].qty = qty;
        items[i].price = price;
    }
    fclose(fi);
    return items;
    
}

void showItems(struct item *arr, int size) {
    for (int i = 0; i < size; i++)
    {
            printf("%d: %s price: %d\n", i+1, arr[i].name, arr[i].price);
    }
    
}



int logIn()
{
    FILE *fp = fopen("employees.txt", "r");
    int numOfEmployees;
    if (fp == NULL)
    {
        printf("File not found\n");
        return 0;
    }
    fscanf(fp, "%d", &numOfEmployees);
    printf("%d employees\n", numOfEmployees);
    struct employee employees[numOfEmployees];
    for (int i = 0; i < numOfEmployees; i++)
    {
        fscanf(fp, "%19s", employees[i].user);
        fscanf(fp, "%19s", employees[i].pass);
    }
    fclose(fp);
    for (int i = 0; i < numOfEmployees; i++)
    {
        for (int j = 0; j < strlen(employees[i].user); j++)
        {
            employees[i].user[j] = employees[i].user[j] ^ 22;
            // employees[i].user[j] = employees[i].pass[j] ^ 22;
        }
        for (int j = 0; j < strlen(employees[i].pass); j++)
        {
            employees[i].pass[j] = employees[i].pass[j] ^ 22;
            // employees[i].user[j] = employees[i].pass[j] ^ 22;
        }
    }
    char un[20];
    char pass[20];
    printf("User: ");
    scanf("%19s", un);
    printf("Password: ");
    scanf("%19s", pass);

    for (int i = 0; i < numOfEmployees; i++)
    {
        if (strcmp(un, employees[i].user) == 0 && strcmp(pass, employees[i].pass) == 0)
        {
            return 1;
        }
    }
    system("cls");
    printf("Incorrect user or password.\n");
    return 0;
}

void Billing(struct item *arr, int size) {
    int choice = 1;
    int qty;
    int bill = 0;
    int amount;
    int change = 0;
    struct billItem bi[size];
    for (int i = 0; i < size; i++)
    {
       strcpy(bi[i].name, " "); 
       bi[i].qty = 0; 
    }
    while (choice > 0 && choice <= size)
    {
        showItems(arr, size);
        printf("Enter item number or any invalid number to exit: ");
        scanf("%d", &choice);
        if (choice <= 0 || choice > size)
        {
            break;
        }
        
        printf("Enter qty: ");
        scanf("%d", &qty);
        if (arr[choice-1].qty >= qty)
        {
            bill += qty * arr[choice - 1].price;
            printf("Item added.\n");
            strcpy(bi[choice-1].name, arr[choice-1].name);
            bi[choice-1].qty = qty;
            arr[choice - 1].qty -= qty;
            sleep(2);
        } else {
            printf("This quantity not available.\n");
            sleep(2);
        }
        system("cls");

        
    }
    system("cls");
    printf("Your Bill:\n");
    for (int i = 0; i < size; i++)
    {
        if (bi[i].qty > 0)
        {
            printf("%d  %s: %d\n", bi[i].qty, bi[i].name, arr[i].price * bi[i].qty);
        }
        
    }
    printf("Total: %d\n", bill);
    pay:
    printf("Enter amount paid: ");
    scanf("%d", &amount);
    if (amount < bill)
    {
        goto pay;
    } else {
        if (amount == bill)
        {
            printf("Paid.\n");
        } else {
            change = amount - bill;
            printf("Paid... change: %d\n", change);
        }
        
    }
    
    FILE *fi = fopen("items.txt", "w");
    fprintf(fi, "%d\n", size);
    for (int i = 0; i < size; i++)
    {
        fprintf(fi, "%s\n", arr[i].name);
        fprintf(fi, "%s\n", arr[i].type);
        fprintf(fi, "%d\n", arr[i].qty);
        fprintf(fi, "%d\n", arr[i].price);
    }
    fclose(fi);
    
    
    
}

void reorder(struct item *arr, int size) {
    int reorderlvl = 50;
    for (int i = 0; i < size; i++)
    {
        if (arr[i].qty <= reorderlvl)
        {
            arr[i].qty += 50;
            printf("ordering %s from supplier....\n", arr[i].name);
        }
        
    }
    FILE *fr = fopen("items.txt", "w");
    fprintf(fr, "%d\n", size);
    for (int i = 0; i < size; i++)
    {
        fprintf(fr, "%s\n", arr[i].name);
        fprintf(fr, "%s\n", arr[i].type);
        fprintf(fr, "%d\n", arr[i].qty);
        fprintf(fr, "%d\n", arr[i].price);
    }
    fclose(fr);
    
}

int main()
{
    int cont = 1;
    int f = 0;
    while (f == 0)
    {
        f = logIn();
    }
    system("cls");
    printf("Logged in.\n");
    sleep(5);
    system("cls");
    struct item *items = getItems();
    int size;
    FILE *fit = fopen("items.txt", "r");
    fscanf(fit, "%d", &size);
    fclose(fit);
    // printf("%d", size);
    // printf("The items that are available in our supermarket: \n");
    // showItems(items, size);
    again:
    Billing(items, size);
    printf("Checking for need of reordering from supplier and updating...\n");
    reorder(items, size);
    sleep(8);
    system("cls");
    printf("Next order? (enter 1 for more orders or 0 to sign out)\n");
    // int cont;
    scanf("%d", &cont);
    if (cont == 1) {
        goto again;
    }
    printf("Signing out...");
    free(items);
    sleep(3);
    return 0;
}