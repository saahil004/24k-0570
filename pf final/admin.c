#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <unistd.h>

struct admin
{
    char user[20];
    char pass[20];
};

struct item
{
    char name[20];
    char type[10];
    int qty;
    int price;
};

int login();
void newItem();
void newEmployee();
void deleteItem();
void deleteEmployee();

void newItem()
{
    struct item newItem;
    int noOfItems;
    char name[20], type[10];
    int qty, price;
    printf("Enter name of the item: ");
    scanf("%19s", name);
    printf("Enter type of the item: ");
    scanf("%9s", type);
    printf("Enter quantity of the item: ");
    scanf("%d", &qty);
    printf("Enter price of the item: ");
    scanf("%d", &price);
    FILE *fi = fopen("items.txt", "r");
    fscanf(fi, "%d", &noOfItems);
    fclose(fi);
    FILE *fip = freopen("items.txt", "r+", fi);
    fprintf(fip, "%d\n", noOfItems + 1);
    fclose(fip);
    FILE *fp = freopen("items.txt", "a", fi);
    fprintf(fp, "%s\n", name);
    fprintf(fp, "%s\n", type);
    fprintf(fp, "%d\n", qty);
    fprintf(fp, "%d\n", price);
    printf("Added.\n");
}

void addEmployee()
{
    int noOfEmployees;
    char newuser[20], newpass[20], cp[20];
    FILE *fp = fopen("employees.txt", "r");
    fscanf(fp, "%d", &noOfEmployees);
    fclose(fp);
    FILE *fbp = freopen("employees.txt", "r+", fp);
    fprintf(fp, "%d\n", noOfEmployees + 1);
    fclose(fbp);
    FILE *fcp = freopen("employees.txt", "a", fp);
    printf("Enter new user: ");
    scanf("%19s", newuser);
    printf("Enter password: ");
    scanf("%19s", newpass);
    printf("Confirm password: ");
    scanf("%19s", cp);
    while (strcmp(newpass, cp) != 0)
    {
        printf("Passwords dont match.\n ");
        printf("Enter password: ");
        scanf("%19s", newpass);
        printf("Confirm password: ");
        scanf("%19s", cp);
    }

    for (int j = 0; j < strlen(newuser); j++)
        {
            newuser[j] = newuser[j] ^ 22;
        }
    for (int j = 0; j < strlen(newpass); j++)
        {
            newpass[j] = newpass[j] ^ 22;
        }
    fprintf(fp, "%s\n", newuser);
    fprintf(fp, "%s\n", newpass);
    fclose(fcp);
    printf("Added.\n");
}

void deleteItem() {
    int noOfItems;
    FILE *file = fopen("items2.txt", "r+");
    fscanf(file, "%d", &noOfItems);
    struct item items[noOfItems];
    char name[20], type[10];
    int qty, price;
    if (noOfItems == 0) {
         printf("No items to delete.\n");
         return;
    }
    for (int i = 0; i < noOfItems; i++)
    {
        fscanf(file, "%s", name);
        strcpy(items[i].name, name);
        fscanf(file, "%s", type);
        strcpy(items[i].type, type);
        fscanf(file, "%d", &qty);
        items[i].qty = qty;
        fscanf(file, "%d", &price);
        items[i].price = price;
    }
    for (int i = 0; i < noOfItems; i++)
    {
        printf("%s  %s  %d %d\n", items[i].name, items[i].type, items[i].qty, items[i].price);
        // printf("%s  %s  %d %d\n", items[i].name);
    }
    fclose(file);
    


}

int login()
{
    FILE *fad = fopen("admin.txt", "r");
    int noOfAdmins;
    fscanf(fad, "%d", &noOfAdmins);
    // printf("%d", noOfAdmins);
    char user[20];
    char pass[20];
    struct admin admins[noOfAdmins];
    for (int i = 0; i < noOfAdmins; i++)
    {
        fscanf(fad, "%19s", user);
        fscanf(fad, "%19s", pass);
        for (int j = 0; j < strlen(user); j++)
        {
            user[j] = user[j] ^ 22;
        }
        for (int j = 0; j < strlen(pass); j++)
        {
            pass[j] = pass[j] ^ 22;
        }
        strcpy(admins[i].user, user);
        strcpy(admins[i].pass, pass);
    }
    fclose(fad);
    char myuser[20];
    char mypass[20];
    printf("Enter user: ");
    scanf("%19s", myuser);
    printf("Enter pass: ");
    scanf("%19s", mypass);
    for (int i = 0; i < noOfAdmins; i++)
    {
        if (strcmp(admins[i].user, myuser) == 0 && strcmp(admins[i].pass, mypass) == 0)
        {
            return 1;
        }
    }
    // printf("Incorrect user or pass.\n");
    printf("Incorrect user or password.\n");
    sleep(2);
    system("cls");
    return 0;
}

int main()
{
    int f = 0;
    while (f == 0)
    {
        f = login();
    }
    system("cls");
    printf("Hello Admin.\n");
    int choice = 0;
    while (choice != 4)
    {
        printf("Enter 1 to add new items to stock.\nEnter 2 to add a new employee.\nEnter 3 to add a new Admin.\nEnter 4 to exit and sign out.");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            newItem();
            sleep(2);
            system("cls");
            break;
        case 2:
            addEmployee();
            sleep(2);
            system("cls");
            break;
        case 3:
            deleteItem();
            // system("cls");
            sleep(10);
            break;
        default:
            break;
        }
    }

    return 0;
}