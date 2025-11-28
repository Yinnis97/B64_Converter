#include "Convert_IM_B64.h"

void Print_Header_Stats(png_header_t png_hdr)
{
    printf(" %s\n %s\n Width %u\n Height : %u\n",
        png_hdr.png_sign,png_hdr.IHDR_verify,
        png_hdr.width,png_hdr.height);
}

uint32_t covert_bigEndian(uint8_t *data,int offset)
{
    // Reads the big endian value from the file, every byte and coverts. 
    return((uint32_t)data[offset] << 24 | (uint32_t)data[offset+1] << 16 | (uint32_t)data[offset+2] << 8 | (uint32_t)data[offset+3] );
}
png_header_t Get_PNG_Header(char* file_buffer)
{
    png_header_t png_header;

    // PNG signature first 8 bytes (0-7)
    strncpy_s(png_header.png_sign,4,file_buffer+INDEX_START_PNG,3);

    // IHDR starts at byte 12 (12-15)
    strncpy_s(png_header.IHDR_verify,5,file_buffer+INDEX_START_IHDR,4);

    // Width starts at byte 16 (16-19)
    png_header.width = covert_bigEndian((uint8_t*)file_buffer,INDEX_START_WIDTH);

    // Height starts at byte 20 (20-23)
    png_header.height = covert_bigEndian((uint8_t*)file_buffer,INDEX_START_HEIGHT);

    // Bit depth
    png_header.bitDepth = (uint8_t)file_buffer[INDEX_START_BITDEPTH];

    // Color type
    png_header.colorType = (uint8_t)file_buffer[INDEX_START_COLTYPE];

    // Compression method
    png_header.compression = (uint8_t)file_buffer[INDEX_START_COMPMET];

    // Filter method
    png_header.filter = (uint8_t)file_buffer[INDEX_START_FILTMET];

    // Interlance method
    png_header.interlace = (uint8_t)file_buffer[INDEX_START_INTERMET];

    return png_header;
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