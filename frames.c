#include "frames.h"
#include <stdint.h>
#include <stdlib.h>

void frames_create(uint8_t* frame,
                   uint8_t frame_len,
                   uint8_t* header,
                   uint8_t* data) {
    // 6B because 2B header, 1B data length, 1B "+", 1B "#" and 1B checksum
    uint8_t data_len = frame_len - 6;

    frame[0] = header[0];
    frame[1] = header[1];
    frame[2] = data_len;
    frame[3] = '+';
    for (uint8_t i = 4; i < data_len; i++) {
        frame[i] = data[i - 4];
    }

    frame[frame_len - 2] = '#';
    frame[frame_len - 1] = frames_calculate_checksum(frame, frame_len);
}

uint8_t frames_calculate_checksum(uint8_t* frame, uint8_t frame_len) {
    uint8_t checksum = frame[0];
    for (uint8_t i = 1; i < frame_len - 1; i++) {
        checksum ^= frame[i];
    }

    return checksum;
}
