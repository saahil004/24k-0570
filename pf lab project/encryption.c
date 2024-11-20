#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
struct employee
{
    char user[20];
    char pass[20];
};
int main() {
    // FILE *fp = fopen("employees.txt", "a");
    FILE *fp = fopen("employees.txt", "r");
    int numOfEmployees;
    if (fp == NULL) {
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
    // fclose(fp);
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
    FILE *f = fopen("employees.txt", "w");
    fprintf(f, "%d\n", numOfEmployees);
    for (int i = 0; i < numOfEmployees; i++)
    {
        fputs(employees[i].user, f);
        fputs("\n", f);
        fputs(employees[i].pass, f);
        fputs("\n", f);
    }
    fclose(f);    


    return 0;
}