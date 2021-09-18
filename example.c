#include <stdio.h>
#include "frames.h"

#define FRAME_LEN 8

// TODO: make example use all functions from frames.h
int main(int argc, char const* argv[]) {
    printf("Hello world!\n\n");

    uint8_t f[FRAME_LEN + 1] = "LD\x02+OK#C\0";  // Wrong CRC!
    printf("Frame: \"%s\"\n", f);                // Print frame
    bool valid = frames_verify(f, FRAME_LEN);  // Check if frame is valid - it's
                                               // invalid because CRC is wrong
    printf("Valid: %d\n\n", valid);            // Print if frame is valid

    frames_create(f, FRAME_LEN, (uint8_t*)"LD",
                  (uint8_t*)"OK");        // Create frame
    printf("Frame: \"%s\"\n", f);         // Print generated frame
    valid = frames_verify(f, FRAME_LEN);  // Check if it is valid
    printf("Valid: %d\n", valid);         // Print if frame is valid
    uint8_t data[3] =
        "\0\0\0";  // Buffer for data which will be extracted from frame
    frames_read_data(f, FRAME_LEN, data);  // Extract data from frame
    printf("Data: \"%s\"\n", data);        // Print this data
    uint8_t len = frames_len_data(f);      // Get data's length
    printf("Data length: %d\n", len);      // Print data's length

    return 0;
}
