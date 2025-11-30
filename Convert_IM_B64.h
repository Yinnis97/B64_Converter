
#ifndef __CONVERT_IM_B64_H__
#define __CONVERT_IM_B64_H__

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stdint.h"

//#define DEBUG_Y

#define MAX_BUFFER_SIZE     	8192        // Maximum image size
#define MAX_USER_INPUT          50          // Maximum user input path

#define INDEX_START_PNG         1           // Start at 1 since PNG start at [1].
#define INDEX_START_IHDR        12          // IHDR chunk start
#define INDEX_START_WIDTH       16          // Width of the image in pixels. (4byte integers).
#define INDEX_START_HEIGHT      20          // Height of the image in pixels. (4byte integers).
#define INDEX_START_BITDEPTH    24          // The number of bits per sample or per palette index. (1byte integer). Valid values are 1, 2, 4, 8, and 16.
#define INDEX_START_COLTYPE     25          // Describes the interpretation of the image data.  (1byte integer).  1 (palette used), 2 (color used), and 4 (alpha channel used). Valid values are 0, 2, 3, 4, and 6.
#define INDEX_START_COMPMET     26          // Indicates the method used to compress the image data. (1byte integer). Always zero.
#define INDEX_START_FILTMET     27          // Indicates the preprocessing method applied to the image data before compression. (1byte integer). Always zero.
#define INDEX_START_INTERMET    28          // Indicates the transmission order of the image data. (1byte integer). 0 (no interlace) or 1 (Adam7 interlace).

#define INDEX_START_IDAT_SIZE   46          // Size of IDAT 
#define INDEX_START_IDAT        50          // IDAT chunk start

static const char Base64_Table[] =
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

typedef struct PNG_HEADER
{
    char png_sign[4];
    char IHDR_verify[5];
    uint32_t chunkdata;
    uint32_t width;
    uint32_t height;
    size_t totalSize;
    uint8_t bitDepth;
    uint8_t colorType;
    uint8_t compression;
    uint8_t filter;
    uint8_t interlace;
    uint32_t idatSize;
}png_header_t;

typedef struct PNG_RESULT
{
    png_header_t png_header;
    uint8_t status;
}png_result_t;

void Set_Blue_Text();
void Set_Red_Text();
void Clean_();

void Print_Header_Stats(png_header_t png_hdr);
size_t Get_Total_Image_Size(FILE *fileptr);
uint32_t Convert_bigEndian(uint8_t *data,int offset);
void ByteTo6Bit(char* file_buffer, size_t filesize, unsigned char* b64_buffer, size_t b64_filesize);
void BitToB64(unsigned char* b64_buffer, size_t b64_filesize);
png_result_t Get_PNG_Header(char* file_buffer, size_t filesize);

#endif