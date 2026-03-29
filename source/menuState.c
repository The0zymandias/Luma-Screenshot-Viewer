#include <stdio.h>
#include <3ds/console.h>
#include <3ds/services/hid.h>

#include "menuState.h"

unsigned int curItemIndex = 0;
unsigned int curPageIndex = 0;
unsigned int maxPageIndex = 0;

const int itemsPerPage = 11;

void menuStatePrint(void) {
    consoleClear();
    printf("|%-46s |\n", "- - - - - - - - - - - - - - - - - - - - - - - -"); // top line
    printf("| %-46s |\n", ""); // blank line

    // Header/title thing, we are just gonna assume for now
    // that no one has tens of thousands of screenshots
    printf("| %s%-34s%s", CONSOLE_CYAN, "Luma Screenshot Viewer", CONSOLE_RESET);
    printf("Page %3d/%3d |\n", curPageIndex + 1, maxPageIndex + 1);

    printf("| %-46s |\n", ""); // blank line

    for (int i = 0; i < itemsPerPage; i++) {
        printf("| %-46s |\n", "");
        if (i == curItemIndex) {
            printf("| %s%-46.46s%s |\n", CONSOLE_GREEN, "> ITEMadaipdfuvboaidfvboaidbvoiadfvbadioufvbaiodfvbidf", CONSOLE_RESET);
        } else {
            printf("| %-45.45s  |\n", " ITEMfgsyhsrtaerihghuiaegbpiebgpieurgbpaeirugbaipdufvbadu");
        }
    }
    printf("| %-46s |\n", "");
    printf("| %-46s |\n", "");
    printf("| %-46s|\n", "- - - - - - - - - - - - - - - - - - - - - - - -"); // bottom line
}

void menuStateHandleInput(int kDown) {
    if (kDown & KEY_DOWN) {
        curItemIndex = (curItemIndex + 1) % itemsPerPage;
    } else if (kDown & KEY_UP) {
        curItemIndex -= 1;
        if (curItemIndex > itemsPerPage-1) {
            curItemIndex = itemsPerPage-1;
        }
    } else if (kDown & KEY_LEFT) {
        curItemIndex = 0;
        curPageIndex -= 1;
        if (curPageIndex > maxPageIndex) {
            curPageIndex = maxPageIndex;
        }
    } else if (kDown & KEY_RIGHT) {
        curItemIndex = 0;
        curPageIndex = (curPageIndex + 1) % (maxPageIndex + 1);
    }
}
