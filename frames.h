#pragma once

// Library cframes provides useful functions to deal with data frames.

#include <stdbool.h>
#include <stdint.h>

// Creates a new frame.
//
// You must allocate memory yourself.
// The frame starts with 2-byte header and contains (frame_len - 7) bytes data.
// Create also calculates the checksum using frames_calculate_checksum.
// Data length must not overflow 249 (256 - 7).
//
// Example frame: LD\x02\x00+OK#C
extern void frames_create(uint8_t* frame,
                          uint8_t frame_len,
                          uint8_t* header,
                          uint8_t* data,
                          uint8_t frame_id);

// Places frame's header into header parameter. It is always 2 bytes.
extern void frames_header(uint8_t* frame, uint8_t* header);

// Places frame's data into data parameter.
extern void frames_read_data(uint8_t* frame, uint8_t frame_len, uint8_t* data);

// Get id of frame
extern uint8_t frames_get_id(uint8_t* frame);

// Returns the length of frame's data in bytes.
extern uint8_t frames_len_data(uint8_t* frame);

// Checks whether the frame is valid (i.e of correct format).
//
// The frame must:
//
// - start with 2 byte uppercase ASCII header
//
// - at 3rd position (2nd index): have a length byte that is equal to the length
// of data
//
// - at 4th position (3rd index): have a plus sign ("+")
//
// - at penultimate position: have a hash sign ("#")
//
// - its checksum must be correct
extern bool frames_verify(uint8_t* frame, uint8_t frame_len);

// Returns length of data part of a frame.
// A valid frame always has:
//
// - 2 byte header
//
// - 1 length byte
//
// - 1 frame id byte
//
// - 1 plus sign ("+")
//
// - 1 hash sign ("#")
//
// - 1 checksum byte
//
// That gives 7 non-data bytes.
extern uint8_t frames_data_len(uint8_t frame_len);

// Calculates the simple CRC checksum of frame.
//
// It takes all frame's bytes into account, except the last byte, because
// the last byte is the checksum itself.
extern uint8_t frames_calculate_checksum(uint8_t* frame, uint8_t frame_len);
