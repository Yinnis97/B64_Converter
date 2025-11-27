#include "Convert_IM_B64.h"

uint32_t covert_bigEndian(uint8_t *data,int offset)
{
    // Reads the big endian value from the file, every byte and coverts. 
    return((uint32_t)data[offset] << 24 | (uint32_t)data[offset+1] << 16 | (uint32_t)data[offset+2] << 8 | (uint32_t)data[offset+3] );
}