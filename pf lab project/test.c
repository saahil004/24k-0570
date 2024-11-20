#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct item* getItems();
int logIn();
void showItems(struct item *arr, int size);
int billGeneration();

struct supplier
{
    char contact[20];
    char name[20];
};


struct item
{
    char name[20];
    char type[10];
    int qty;
    int price;
    // struct supplier supplier;
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

int main()
{
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
    // printf("%d", size);
    printf("The items that are available in our supermarket: \n");
    showItems(items, size);
    return 0;
}