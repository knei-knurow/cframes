#include "frames.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void frames_create(uint8_t* frame,
                   uint8_t frame_len,
                   uint8_t* header,
                   uint8_t* data) {
    // 6B because 2B header, 1B data length, 1B "+", 1B "#" and 1B checksum
    uint8_t data_len = frames_data_len(frame_len);

    frame[0] = header[0];
    frame[1] = header[1];
    frame[2] = data_len;
    frame[3] = '+';
    memcpy(frame + 4, data, data_len);
    frame[frame_len - 2] = '#';
    frame[frame_len - 1] = frames_calculate_checksum(frame, frame_len);
}

void frames_header(uint8_t* frame, uint8_t* header) {
    header[0] = frame[0];
    header[1] = frame[1];
}

void frames_read_data(uint8_t* frame, uint8_t frame_len, uint8_t* data) {
    memcpy(data, frame + 4, frame_len - 6);
}

uint8_t frames_len_data(uint8_t* frame) {
    return frame[2];
}

bool frames_verify(uint8_t* frame, uint8_t frame_len) {
    if (frame[0] < 'A' || frame[0] > 'Z') {
        return false;
    }

    if (frame[1] < 'A' || frame[1] > 'Z') {
        return false;
    }

    if (frame[2] != frames_data_len(frame_len)) {
        return false;
    }

    if (frame[3] != '+') {
        return false;
    }

    if (frame[frame_len - 2] != '#') {
        return false;
    }

    uint8_t checksum = frames_calculate_checksum(frame, frame_len);
    return checksum == frame[frame_len - 1];
}

uint8_t frames_data_len(uint8_t frame_len) {
    return frame_len - 6;
}

uint8_t frames_calculate_checksum(uint8_t* frame, uint8_t frame_len) {
    uint8_t checksum = frame[0];
    for (uint8_t i = 1; i < frame_len - 1; i++) {
        checksum ^= frame[i];
    }

    return checksum;
}
