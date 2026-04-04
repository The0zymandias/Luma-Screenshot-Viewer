#include <stdlib.h>
#include <stdio.h>

bool is24BitBitmap(FILE *file) {
    fpos_t pos;
    fgetpos(file, &pos);
    fseek(file, 0x1C, SEEK_SET);
    unsigned short bitsPerPixel;

    fread(&bitsPerPixel, sizeof(unsigned short), 1, file);
    fsetpos(file, &pos);
    return bitsPerPixel == 24;
}
