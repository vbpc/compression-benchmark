#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "bcl-1.2.0/src/rle.c"

static struct timeval time_start;
static struct timeval time_end;

int main(int argc, char *argv[]) {
    FILE *f = fopen(argv[1], "rb");
    if (!f) {
        return 0;
    }

    fseek(f, 0, SEEK_END);
    long file_size = ftell(f);
    fseek(f, 0, SEEK_SET);

    if (file_size >= 0x100000000)
        file_size = 0xFFFFFFFF;

    void* inpbuffer = malloc((size_t) file_size);
    void* outbuffer = malloc((size_t) file_size);

    fread(inpbuffer, 1, (size_t) file_size, f);

    gettimeofday(&time_start, NULL);
    unsigned int compressed_size = RLE_Compress(inpbuffer, outbuffer, (unsigned int) file_size);
    gettimeofday(&time_end, NULL);

    printf("Duration: %lu\n", ((time_end.tv_sec * 1000) + (time_end.tv_usec / 1000)) - ((time_start.tv_sec * 1000) + (time_start.tv_usec / 1000)));
    printf("Original: %lu\n",file_size);
    printf("Compressed: %u\n",compressed_size);
}