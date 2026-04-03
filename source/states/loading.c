#include <stdio.h>
#include <3ds/console.h>

#include "states/loading.h"

void loadingStatePrint() {
    consoleClear();
    printf("|%-46s |\n", "- - - - - - - - - - - - - - - - - - - - - - - -"); // top line
    printf("| %-46s |\n", ""); // blank line
    printf("| %s%-46.46s%s |\n", "\x1b[36;1m", "Luma Screenshot Viewer", "\x1b[0m");
    printf("| %-46s |\n", ""); // blank line

    for (int i = 0; i < 10; i++) {
        printf("| %-46s |\n", "");
        printf("| %-46s |\n", "> ITEM");
    }
    printf("| %-46s |\n", "");
    printf("| %-46s |\n", "");
    printf("| %-46s |\n", "");
    printf("| %-46s|\n", "- - - - - - - - - - - - - - - - - - - - - - - -"); // bottom line
}
