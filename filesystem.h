#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#define NAME_SIZE 50

// Structure for a file node.
typedef struct File {
    char name[NAME_SIZE];
    int size;
    struct File *next;  // Next file in the same directory.
} File;

// Structure for a directory node.
typedef struct Directory {
    char name[NAME_SIZE];
    struct Directory *parent;
    struct Directory *subdirs; // Head of linked list of subdirectories.
    struct Directory *next;    // Next sibling directory.
    File *files;               // Head of linked list of files in this directory.
} Directory;

// Function prototypes
Directory* createDirectory(Directory *parent, const char *name);
File* createFile(const char *name, int size);
Directory* searchDirectory(Directory *current, const char *name);
void listDirectory(Directory *dir, int depth);
void searchItem(Directory *dir, const char *target);
void freeDirectory(Directory *dir);

#endif  // FILESYSTEM_H
