#ifndef VAULT_H
#define VAULT_H
#include <time.h>
 typedef struct {
    char filename[50];
    char locked_filename[50];
    char password[30];
    time_t locker_time;
    int pass_attempts;
 } Vault;

 void create_locker();
 void access_locker();
 void delete_locker();
 void edit_locker();
#endif
