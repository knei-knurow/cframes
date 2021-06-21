#include "frames.h"
#include <stdint.h>
#include <stdlib.h>

// TODO: decide whether dynamic memory allocation is really needed

uint8_t* frames_create(uint8_t* header, uint8_t* data, uint8_t data_len) {
    uint8_t frame_len = 2 + 2 + data_len + 2;
    uint8_t* frame = malloc(sizeof(uint8_t) * frame_len);

    frame[0] = header[0];
    frame[1] = header[1];
    frame[2] = data_len;
    frame[3] = '+';
    for (uint8_t i = 0, j = 4; i < data_len; i++) {
        frame[j] = data[i];
    }

    frame[frame_len - 2] = '+';
    frame[frame_len - 1] = frames_calculate_checksum(frame, frame_len);
    return frame;
}

uint8_t frames_calculate_checksum(uint8_t* frame, uint8_t frame_len) {
    uint8_t checksum = frame[0];
    for (uint8_t i = 1; i < frame_len - 1; i++) {
        checksum ^= frame[i];
    }

    return checksum;
}
