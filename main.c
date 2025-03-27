#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "filesystem.h"


int main(int argc, char** argv) {

    //Creating root for use througout program directory
    Directory* root = createDirectory(NULL, "root");
    Directory* parent;
    int choice = 0;
    int file_size = 0;
    char name[NAME_SIZE];
    char parent_name[NAME_SIZE];

    while(1) {

        printf("\n===========Toy File System Menu==========\n");
        printf("1. Create a new directory\n");
        printf("2. Create a new file\n");
        printf("3. List contents\n");
        printf("4. Search for a file\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        //Check for valid input before proceeding
        if (scanf("%d", &choice) != 1) {
            printf("Something went wrong!\n");
            freeDirectory(root);
            return EXIT_FAILURE;
        }

        switch (choice) {
            case 1:
                printf("Enter the name of the directory: ");
                scanf(" %[^\n]", name);
                printf("Enter parent directory name (or 'root'): ");
                scanf(" %[^\n]", parent_name);
                parent = searchDirectory(root, parent_name);
                if (!parent) {
                    printf("Parent directory '%s' not found :(\n", parent_name);
                    break;
                }
                if (searchDirectory(parent -> subdirs, name)) {
                    printf("Directory '%s' already exists under '%s'.\n", name, parent_name);
                    break;
                }
                Directory* new_dir = createDirectory(parent, name);
                new_dir -> next = parent -> subdirs;
                parent -> subdirs = new_dir;
                printf("Directory '%s' created under '%s'.\n", name, parent_name);
                break;
            
            case 2:
                printf("Enter file name: ");
                scanf(" %[^\n]", name);
                printf("Enter file size (in bytes): ");
                scanf("%d", &file_size);
                printf("Enter parent directory name (or 'root'): ");
                scanf(" %[^\n]", parent_name);
                parent = searchDirectory(root, parent_name);
                if (!parent) {
                    printf("Parent directory '%s' not found :(\n", parent_name);
                    break;
                }
                int duplicate = 0;
                for (File* f = parent -> files; f; f = f -> next) {
                    if (strcmp(f -> name, name) == 0) {
                        duplicate = 1;
                        break;
                    }
                }
                if (duplicate) {
                    printf("File '%s' already exists under '%s'.\n", name, parent_name);
                    break;
                }
                File* new_file = createFile(name, file_size);
                new_file -> next = parent -> files;
                parent -> files = new_file;
                printf("File '%s' created under '%s'.\n", name, parent_name);
                break;
            
            case 3:
                printf("Enter directory name to list: ");
                 scanf(" %[^\n]", parent_name);
                Directory* dir = searchDirectory(root, parent_name);
                if (!dir) {
                    printf("Directory '%s' not found :(\n", parent_name);
                } else {
                    printf("\nContents of '%s':\n", parent_name);
                    listDirectory(dir, 0);
                }
                break;
            
            case 4:
                printf("Enter name to search for: ");
                 scanf(" %[^\n]", name);
                printf("Results:\n");
                searchItem(root, name);
                break;

            case 5:
                freeDirectory(root);
                printf("All memory freeeeeeed!!\n");
                return EXIT_SUCCESS;
            
            default:
                printf("Nothing happened...try something else?\n");
        }

    }

    return EXIT_SUCCESS;

}