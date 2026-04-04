#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "screenshots.h"

char **screenshotNames;

u32 numScreenshots = 0;

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

void formatScreenshotNames() {
    for (int i = 0; i < numScreenshots; i++) {
        char *curName = screenshotNames[i];
        // printf("%d %s\n", i, curName);

        for (int j = 0; j < 10; j++) {
            if (curName[j] == '-') {
                char *address = curName + j;
                *address = '/';
            }
        }
        curName[10] = ' ';

        for (int j = 11; j < 20; j++) {
            if (curName[j] == '-') {
                char *address = curName + j;
                *address = ':';
            }
        }
    }

    // printf("%s\n", screenshotNames[0]);
}

void getScreenshotNamesFromDir() {
    numScreenshots = 666;
    screenshotNames = malloc(numScreenshots * sizeof(char*));
    for (int i = 0; i < numScreenshots; i++) {
        screenshotNames[i] = strdup("2026-02-18_08-13-29.908");
    }
}

void loadScreenshotNames() {
    getScreenshotNamesFromDir();
    formatScreenshotNames();
    return;
}
