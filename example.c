#include <stdio.h>
#include "frames.h"

#define FRAME_LEN 8

// TODO: make example use all functions from frames.h
int main(int argc, char const* argv[]) {
    printf("hello world\n");

    uint8_t f[FRAME_LEN] = {'L', 'D', '2', '+', 'O', 'K', '#', 'C'};
    bool valid = frames_verify(f, FRAME_LEN);
    printf("valid: %d\n", valid);
    return 0;
}
