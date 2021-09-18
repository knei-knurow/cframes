#include <stdio.h>
#include "frames.h"

#define FRAME_LEN 8

// TODO: make example use all functions from frames.h
int main(int argc, char const* argv[]) {
    printf("Hello world!\n\n");

    uint8_t f[FRAME_LEN + 1] = "LD\x02+OK#C\0";  // Wrong CRC!
    printf("Frame: \"%s\"\n", f);
    bool valid = frames_verify(f, FRAME_LEN);
    printf("Valid: %d\n\n", valid);

    frames_create(f, FRAME_LEN, (uint8_t*)"LD", (uint8_t*)"OK");
    printf("Frame: \"%s\"\n", f);
    valid = frames_verify(f, FRAME_LEN);
    printf("Valid: %d\n", valid);
    uint8_t data[3] = "\0\0\0";
    frames_read_data(f, FRAME_LEN, data);
    printf("Data: \"%s\"\n", data);
    uint8_t len = frames_len_data(f);
    printf("Data length: %d\n", len);

    return 0;
}
