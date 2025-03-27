#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filesystem.h"

// Create a new directory node.
Directory* createDirectory(Directory *parent, const char *name) {
    Directory *dir = malloc(sizeof(Directory));
    if (!dir) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    strncpy(dir->name, name, NAME_SIZE);
    dir->parent = parent;
    dir->subdirs = NULL;
    dir->files = NULL;
    dir->next = NULL;
    return dir;
}

// Create a new file node.
File* createFile(const char *name, int size) {
    File *file = malloc(sizeof(File));
    if (!file) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    strncpy(file->name, name, NAME_SIZE);
    file->size = size;
    file->next = NULL;
    return file;
}

// Recursively search for a directory by name. Returns pointer if found; otherwise NULL.
Directory* searchDirectory(Directory *current, const char *name) {
    if (!current)
        return NULL;
    if (strcmp(current->name, name) == 0)
        return current;
    // Check subdirectories recursively.
    for (Directory *sub = current->subdirs; sub; sub = sub->next) {
        Directory *found = searchDirectory(sub, name);
        if (found)
            return found;
    }
    return NULL;
}

// Recursively list the contents of a directory.
void listDirectory(Directory *dir, int depth) {
    for (int i = 0; i < depth; i++)
        printf("  ");
    printf("[DIR] %s\n", dir->name);

    // List files.
    for (File *f = dir->files; f; f = f->next) {
        for (int i = 0; i < depth + 1; i++)
            printf("  ");
        printf("- %s (size: %d bytes)\n", f->name, f->size);
    }

    // List subdirectories.
    for (Directory *sub = dir->subdirs; sub; sub = sub->next)
        listDirectory(sub, depth + 1);
}

// Recursively search for an item (directory or file) by name and print its full path.
void searchItem(Directory *dir, const char *target) {
    // Check if current directory matches.
    if (strcmp(dir->name, target) == 0) {
        // Build and print the full path.
        if (dir->parent) {
            searchItem(dir->parent, ""); // Print parent's path.
            printf("/%s\n", dir->name);
        } else {
            printf("%s\n", dir->name);
        }
    }
    // Check files in current directory.
    for (File *f = dir->files; f; f = f->next) {
        if (strcmp(f->name, target) == 0) {
            // Build and print the full path.
            if (dir->parent) {
                searchItem(dir->parent, ""); // Print parent's path.
                printf("/%s/%s\n", dir->name, f->name);
            } else {
                printf("%s/%s\n", dir->name, f->name);
            }
        }
    }
    // Recurse into subdirectories.
    for (Directory *sub = dir->subdirs; sub; sub = sub->next)
        searchItem(sub, target);
}

// Recursively free memory for directories and files.
void freeDirectory(Directory *dir) {
    if (!dir)
        return;
    // Free subdirectories.
    Directory *sub = dir->subdirs;
    while (sub) {
        Directory *next = sub->next;
        freeDirectory(sub);
        sub = next;
    }
    // Free files.
    File *f = dir->files;
    while (f) {
        File *next = f->next;
        free(f);
        f = next;
    }
    free(dir);
}
