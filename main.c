#include<stdio.h>
#include "vault.h"

int main() {
    printf("Timefile Project\n");
    int n;
    while(1){
        printf("\nMENU\n1. Create Vault\n2. Access Vault\n3. Delete Vault\n4. Edit File\n5. Exit\nEnter your choice: ");
        scanf("%d", &n);
        if (n == 1) {
            create_locker();
        } else if (n == 2) {
            access_locker();
        } else if (n == 3) {
            delete_locker();
        } else if (n == 4) {
            edit_locker();
        } else if (n == 5) {
            break;
        } else {
            printf("Invalid Choice\n");
        }
    }
    return 0;
}