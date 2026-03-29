#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>

const char *screenshot[24];

// Not even gonna lie, I asked AI to write this function for me
int numFilesInDir(const char *path) {
    DIR *dir = opendir(path);
    if (!dir)
        return 0;

    int count = 0;
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char fullPath[512];
        snprintf(fullPath, sizeof(fullPath), "%s/%s", path, entry->d_name);

        struct stat st;
        if (stat(fullPath, &st) != 0)
            continue;  // couldn't stat, skip it

        if (S_ISREG(st.st_mode))  // only count regular files
            count++;
    }
    closedir(dir);
    return count;
}

void getAllScreenshotNames() {
    return;
}
