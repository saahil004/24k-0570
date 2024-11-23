#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <unistd.h>

struct employee
{
    char user[20];
    char pass[20];
};

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
    FILE *fip = freopen("items.txt", "r+", fi);
    fprintf(fip, "%d\n", noOfItems + 1);
    fclose(fip);
    FILE *fp = freopen("items.txt", "a", fi);
    fprintf(fp, "%s\n", name);
    fprintf(fp, "%s\n", type);
    fprintf(fp, "%d\n", qty);
    fprintf(fp, "%d\n", price);
    printf("Added.\n");
    fclose(fi);
}

void addEmployee()
{
    int noOfEmployees;
    char newuser[20], newpass[20], cp[20];
    FILE *fop = fopen("employees.txt", "r");
    fscanf(fop, "%d", &noOfEmployees);
    struct employee employees[noOfEmployees];
    char user[20], pass[20];
    for (int i = 0; i < noOfEmployees; i++)
    {
        fscanf(fop, "%s", user);
        fscanf(fop, "%s", pass);
        for (int j = 0; j < strlen(user); j++)
        {
            user[j] = user[j] ^ 22;
        }
        for (int j = 0; j < strlen(pass); j++)
        {
            pass[j] = pass[j] ^ 22;
        }
        printf("%d :%s\n", i+1, user);
        strcpy(employees[i].user, user);
        strcpy(employees[i].pass, pass);
    }
    fclose(fop);
    
    FILE *fp = fopen("employees.txt", "r");
    fscanf(fp, "%d", &noOfEmployees);
    fclose(fp);
    FILE *fbp = freopen("employees.txt", "r+", fp);
    fprintf(fp, "%d\n", noOfEmployees + 1);
    fclose(fbp);
    FILE *fcp = freopen("employees.txt", "a", fp);
    make:
    printf("Enter new user: ");
    scanf("%19s", newuser);
    
    for (int i = 0; i < noOfEmployees; i++)
    {
        if (strcmp(newuser, employees[i].user) == 0)
        {
            printf("User already exists.\n");
            goto make;
        }
        
    }
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
    int f = 0;
    FILE *file = fopen("items.txt", "r+");
    fscanf(file, "%d", &noOfItems);
    struct item items[noOfItems];
    char name[20], type[10];
    int qty, price;
    if (noOfItems == 0) {
         printf("No items to delete.\n");
         return;
    }
    printf("%d\n", noOfItems);
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
    printf("Enter item to be deleted: ");
    char del[20];
    scanf("%19s", del);
    for (int i = 0; i < noOfItems; i++)
    {
        if (strcmp(items[i].name, del) == 0)
        {
            f = 1;
        }
        
    }
    if (f == 0)
    {
        printf("Item not found.\n");
        return;
    }
    
    FILE *fd = freopen("items.txt", "w", file);
    fprintf(fd, "%d\n", noOfItems - 1);
    for (int i = 0; i < noOfItems; i++)
    {
        if (strcmp(items[i].name, del) == 0)
        {
            continue;
        } else {
            fprintf(fd, "%s\n", items[i].name);
            fprintf(fd, "%s\n", items[i].type);
            fprintf(fd, "%d\n", items[i].qty);
            fprintf(fd, "%d\n", items[i].price);
        }
    }
    printf("Deleted.\n");
    fclose(fd);
    
    


}

void deleteEmployee() {
    int noOfEmployees;
    char user[20], pass[20];
    int f = 0;
    FILE *fp = fopen("employees.txt", "r");
    fscanf(fp, "%d", &noOfEmployees);
    struct employee employees[noOfEmployees];
    for (int i = 0; i < noOfEmployees; i++)
    {
        fscanf(fp, "%s", user);
        fscanf(fp, "%s", pass);
        for (int j = 0; j < strlen(user); j++)
        {
            user[j] = user[j] ^ 22;
        }
        for (int j = 0; j < strlen(pass); j++)
        {
            pass[j] = pass[j] ^ 22;
        }
        printf("%d :%s\n", i+1, user);
        strcpy(employees[i].user, user);
        strcpy(employees[i].pass, pass);
    }
    fclose(fp);   
    printf("Enter user of employee to be kicked: ");
    char nuser[20];
    scanf("%19s", nuser);
    for (int i = 0; i < noOfEmployees; i++)
    {
        if (strcmp(employees[i].user, nuser) == 0)
        {
            f = 1;
            break;
        }
        
    }
    if (f == 0)
    {
        printf("User not found.\n");
        return;
    }
    FILE *fde = freopen("employees.txt", "w", fp);
    fprintf(fde, "%d\n", noOfEmployees - 1);
    for (int i = 0; i < noOfEmployees; i++)
    {
        if (strcmp(employees[i].user, nuser) == 0)
        {
             continue;
        } else {
            for (int j = 0; j < strlen(employees[i].user); j++)
            {
                employees[i].user[j] = employees[i].user[j] ^ 22;
            }
            for (int j = 0; j < strlen(employees[i].pass); j++)
            {
                employees[i].pass[j] = employees[i].pass[j] ^ 22;
            }
            fprintf(fde, "%s\n", employees[i].user);
            fprintf(fde, "%s\n", employees[i].pass);
        }
        
    }
    printf("User deleted.\n");
    fclose(fde); 
}

int login()
{
    printf("Admin Login\n");
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
    while (choice != 5)
    {
        printf("Enter 1 to add new items to stock.\nEnter 2 to add a new employee.\nEnter 3 to delete an item from available stock.\nEnter 4 to kick an employee.\nEnter 5 to sign out.\nChoice: ");
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
            sleep(5);
            system("cls");
            break;
        case 4:
            deleteEmployee();
            sleep(5);
            system("cls");
            break;
        }
    }

    return 0;
}