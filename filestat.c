#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>

// Structure to hold file/directory properties
typedef struct {
    char type;
    long long size;
    char last_modified_time[20]; // YYYY-MM-DD HH:MM:SS\0
    char name[256]; // To store the file/folder name
} FileProperty;

int main() {
    char path[1024];
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    FileProperty *properties = NULL;
    int count = 0;
    int capacity = 10; // Initial capacity for the dynamic array

    printf("Enter the path to a directory: ");
    if (fgets(path, sizeof(path), stdin) == NULL) {
        perror("Thu muc khong ton tai");
        return 1;
    }

    // Remove trailing newline character if present
    path[strcspn(path, "\n")] = 0;

    // Check if the path is valid and directory exists
    dir = opendir(path);
    if (dir == NULL) {
        if (errno == ENOENT) {
            fprintf(stderr, "Error: Directory '%s' does not exist.\n", path);
        } else if (errno == ENOTDIR) {
            fprintf(stderr, "Error: '%s' is not a directory.\n", path);
        } else {
            perror("Error opening directory");
        }
        return 1;
    }

    // Allocate initial memory for the properties array
    properties = (FileProperty *)malloc(capacity * sizeof(FileProperty));
    if (properties == NULL) {
        perror("Failed to allocate memory");
        closedir(dir);
        return 1;
    }

    // Read all entries in the directory
    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".." entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Construct full path for stat()
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        if (stat(full_path, &file_stat) == -1) {
            perror("Error getting file status");
            continue; // Skip to the next entry
        }

        // Resize array if capacity is reached
        if (count == capacity) {
            capacity *= 2;
            FileProperty *temp = (FileProperty *)realloc(properties, capacity * sizeof(FileProperty));
            if (temp == NULL) {
                perror("Failed to reallocate memory");
                // Free already allocated memory and close directory before exiting
                free(properties);
                closedir(dir);
                return 1;
            }
            properties = temp;
        }

        // Populate the FileProperty struct
        switch (file_stat.st_mode & S_IFMT) {
            case S_IFDIR:  properties[count].type = 'd'; break;
            case S_IFREG:  properties[count].type = '-'; break;
            case S_IFLNK:  properties[count].type = 'l'; break;
            case S_IFIFO:  properties[count].type = 'p'; break;
            case S_IFSOCK: properties[count].type = 's'; break;
            case S_IFCHR:  properties[count].type = 'c'; break;
            case S_IFBLK:  properties[count].type = 'b'; break;
            default:       properties[count].type = '?'; break;
        }

        properties[count].size = file_stat.st_size;

        struct tm *timeinfo;
        timeinfo = localtime(&file_stat.st_mtime);
        if (timeinfo != NULL) {
            strftime(properties[count].last_modified_time, sizeof(properties[count].last_modified_time), "%Y-%m-%d %H:%M:%S", timeinfo);
        } else {
            strcpy(properties[count].last_modified_time, "N/A");
        }
        
        strncpy(properties[count].name, entry->d_name, sizeof(properties[count].name) - 1);
        properties[count].name[sizeof(properties[count].name) - 1] = '\0'; // Ensure null termination

        count++;
    }

    closedir(dir);

    // Display the properties
    printf("\nFile/Folder Properties in '%s':\n", path);
    printf("%-5s %-10s %-20s %s\n", "Type", "Size", "Last Modified", "Name");
    printf("----- ---------- -------------------- -----------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-5c %-10lld %-20s %s\n", 
               properties[i].type, 
               properties[i].size, 
               properties[i].last_modified_time,
               properties[i].name);
    }

    free(properties); // Free allocated memory

    return 0;
}
