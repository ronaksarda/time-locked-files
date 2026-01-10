#include<stdio.h>
#include "vault.h"
#include<string.h>
#include<time.h>
#include<stdlib.h>

int if_file_exist( const char *filename){ //check file existence
    FILE *fp;
    fp = fopen(filename,"rb");
    if (fp){
        fclose(fp);
        return 1;
    }
    return 0;
}

void protect(char *str) //hide text by bitwise operations
{
    for(int i = 0; str[i] != '\0' ; i++){
        str[i] ^= 0xAA;
    }
}

void changetype(const char *source , const char *destination){ //decrpyting the file to readable format and vice versa
    FILE *input , *output;
    input = fopen(source,"rb");
    output = fopen(destination,"wb");
    if(input == NULL || output == NULL) {
        if (input) fclose(input);
        if (output) fclose(output);
        return;
    }
    char letter;
    while((letter = fgetc(input)) != EOF){
        fputc(letter ^ 0xAA , output);
    }
    fclose(input);
    fclose(output);
}

void create_locker(){
    int minutes;
    Vault v1;
    printf("Enter filename: "); //entering filename( to create locker)
    scanf("%s",v1.filename);
    
    if (!if_file_exist(v1.filename)){
        printf("File does not exist!\n");
        return;
    }

    snprintf(v1.locked_filename, sizeof(v1.locked_filename), "%s.locked", v1.filename); //creating locked file name
    printf("Enter password to lock the file: "); //password to lock the file
    scanf("%s",v1.password);
    protect(v1.password); //protecting password by bitwise operation
    v1.pass_attempts = 0;

    printf("Enter time duration to lock the file (in minutes): ");
    if (scanf("%d",&minutes) != 1) {
        return;
    }
    v1.locker_time = time(NULL) + (minutes * 60); //calculating locker time

    changetype(v1.filename , v1.locked_filename);

    // ensure encryption succeeded before appending record and deleting original
    if (!if_file_exist(v1.locked_filename)) {
        // encryption failed; do not remove original
        return;
    }

    FILE *fp = fopen("vault.dat","ab");
    if(fp == NULL){
        // cannot open vault.dat; cleanup created locked file and return
        remove(v1.locked_filename);
        return;
    }
    fwrite(&v1,sizeof(Vault),1,fp); //storing vault info in vault.dat
    fclose(fp);

    remove(v1.filename); //removing original file

    printf("File locked successfully!\n");
}

void access_locker(){ 
    Vault v1;
    char target_filename[50];
    printf("Enter filename to access: ");
    scanf("%s",target_filename); //entering filename to access

    FILE *fp = fopen("vault.dat","r+b"); //opening vault.dat to read vault info
    if(fp == NULL){
        printf("No vault found!\n");
        return;
    }
    int check = 0;
    long pos = 0;
    while(fread(&v1,sizeof(Vault),1,fp) == 1){
        if(strcmp(v1.filename,target_filename) == 0){
            check =1 ;
            pos = ftell(fp) - (long)sizeof(Vault); //storing position to update record
            break;
        }
    }
    if(!check){
        printf("Vault for the given file does not exist!\n");
        fclose(fp);
        return;
    }

    if(v1.pass_attempts >= 3){ //checking pass attempts
        printf("Maximum password attempts exceeded!\n");
        fclose(fp);
        return;
    }

    printf("Enter password: ");
    char pass[30];
    scanf("%s",pass);
    protect(pass); //protecting entered password

    if (strcmp(pass, v1.password) != 0) {   //comparing password
        v1.pass_attempts++;
        fseek(fp, pos, SEEK_SET); //moving file pointer to update pass attempts
        fwrite(&v1, sizeof(Vault), 1, fp);
        fflush(fp);
        fclose(fp);
        printf("Incorrect password! Attempts left : %d\n" , 3-v1.pass_attempts); 
        return;
    }

    time_t current_time = time(NULL); //checking time to unlock
    if (current_time < v1.locker_time){
        printf("File is still locked for %ld more seconds!\n", (long)(v1.locker_time - current_time));
        printf("Enter Emergency Override Key (or 'skip'): ");
        char override[20];
        scanf("%s", override);
        if(strcmp(override, "ADMIN") != 0) { //comparing override key
            fclose(fp);
            return;
        }
        // else override accepted, continue
    }

    v1.pass_attempts = 0; //resetting pass attempts
    fseek(fp, pos, SEEK_SET);
    fwrite(&v1, sizeof(Vault), 1, fp); //set cursor to update pass attempts
    fflush(fp);
    fclose(fp);

    changetype(v1.locked_filename, v1.filename);
    remove(v1.locked_filename);
    printf("File unlocked successfully!\n");
}

void delete_locker(){
    Vault v1;
    char target_filename[50];
    printf("Enter filename to delete: ");
    scanf("%s", target_filename); //entering filename to delete

    FILE *fp = fopen("vault.dat", "rb"); //opening vault.dat
    if (!fp) return;
    FILE *temp = fopen("temp.dat", "wb"); //creating temp file
    if (!temp) { fclose(fp); return; }

    int found = 0;

    while (fread(&v1, sizeof(Vault), 1, fp) == 1) {
        if (strcmp(v1.filename, target_filename) == 0) {
            found = 1;
            remove(v1.locked_filename); //removing original file
            printf("Record deleted.\n");
        } else {
            fwrite(&v1, sizeof(Vault), 1, temp); //storing vault info in temp.dat
        }
    }
    fclose(fp);
    fclose(temp);
    remove("vault.dat"); //removing original vault file
    rename("temp.dat", "vault.dat"); //renaming temp file
}

void edit_locker(){
    Vault v1;
    char target_filename[50];
    printf("Enter filename to edit: ");
    scanf("%s",target_filename); //entering filename to edit

    FILE *fp = fopen("vault.dat","rb");
    if (!fp) return;
    int check = 0;
    while(fread(&v1,sizeof(Vault),1,fp) == 1){
        if(strcmp(v1.filename,target_filename) == 0){
            check = 1;
            break;
        }
    }
    fclose(fp);

    if(!check){
        printf("File not found!\n");
        return;
    }

    changetype(v1.locked_filename, v1.filename); //decrypting for editing
    printf("File is now open for editing. Save changes in your editor.\n");
    printf("Press any key then ENTER to re-lock...");
    char pause[10];
    scanf("%s", pause); //waiting for user input

    changetype(v1.filename, v1.locked_filename); //encrypting after editing
    remove(v1.filename); //removing original file
    printf("File re-locked successfully!\n");
}
