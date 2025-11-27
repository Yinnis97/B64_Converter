
#ifndef __CONVERT_IM_B64_H__
#define __CONVERT_IM_B64_H__

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stdint.h"

#define MAX_INPUT_SIZE	8192

typedef struct PNG_HEADER
{
    char png_sign[4];
    char IHDR_verify[5];
    uint32_t width;
    uint32_t height;
}png_header_t;

uint32_t covert_bigEndian(uint8_t *data,int offset);


#endif