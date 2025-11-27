#include "Convert_IM_B64.h"

uint32_t covert_bigEndian(uint8_t *data,int offset)
{
    // Reads the big endian value from the file, every byte and coverts. 
    return((uint32_t)data[offset] << 24 | (uint32_t)data[offset+1] << 16 | (uint32_t)data[offset+2] << 8 | (uint32_t)data[offset+3] );
}

void Set_Blue_Text()
{
    printf("\033[38;2;5;70;180m");
}

void Set_Red_Text()
{
    printf("\033[38;2;255;0;0m");
}

void Clean_()
{
    printf("\033[0m");
}