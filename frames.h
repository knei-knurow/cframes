// Library cframes provides useful functions to deal with data frames.

#include <stdbool.h>
#include <stdint.h>

// Creates a new frame.
// The frame starts with header and contains data.
// Create also calculates the checksum using frames_calculate_checksum.
// Data length must not overflow byte.
uint8_t* frames_create(uint8_t* header, uint8_t* data, uint8_t data_len);

// Header returns frame's header. It is always 2 bytes.
uint8_t frames_header(uint8_t* frame);

// Returns frame's data part from the first byte after a plus sign ("+") up
// to the antepenultimate (last but one - 1) byte.
uint8_t* frames_data(uint8_t frame, uint8_t data_len);

// Returns the length of frame's data in bytes.
uint8_t frames_len_data(uint8_t* frame);

// Checks whether the frame is valid (i.e of correct format).
//
// The frame must:
//
// - start with 2 byte uppercase ASCII header
//
// - at 3rd position (2nd index): have a length byte that is equal to the length of data
//
// - at 4th position (3rd index): have a plus sign ("+")
//
// - at penultimate position: have a hash sign ("#")
//
// - its checksum must be correct
bool frames_verify(uint8_t* frame, uint8_t frame_len);

// Calculates the simple CRC checksum of frame.
//
// It takes all frame's bytes into account, except the last byte, because
// the last byte is the checksum itself.
uint8_t frames_calculate_checksum(uint8_t* frame, uint8_t frame_len);
