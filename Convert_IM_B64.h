
#ifndef __CONVERT_IM_B64_H__
#define __CONVERT_IM_B64_H__

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stdint.h"

#define MAX_BUFFER_SIZE	8192
#define MAX_USER_INPUT  50

typedef struct PNG_HEADER
{
    char png_sign[4];
    char IHDR_verify[5];
    uint32_t chunkdata;
    uint32_t width;
    uint32_t height;
    uint32_t totalSize;
    uint8_t colorByteSize;
    uint8_t colorType;
    uint8_t compression;
    uint8_t filter;
    uint8_t enlacement;
}png_header_t;

uint32_t covert_bigEndian(uint8_t *data,int offset);


#endif