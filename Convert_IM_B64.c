#include "Convert_IM_B64.h"

void Print_Header_Stats(png_header_t png_hdr)
{
    printf("Is a PNG : ");
    if(strcmp(png_hdr.png_sign,"PNG") == 0)
    {
        printf("Yes\n");
        printf("Width               : %u pixels\n",png_hdr.width);
        printf("Height              : %u pixels\n",png_hdr.height);
        printf("Bit depth           : %d\n",png_hdr.bitDepth);
        printf("Color Type          : %d\n",png_hdr.colorType );
        printf("Compression method  : %d\n",png_hdr.compression);
        printf("Filter method       : %d\n",png_hdr.filter);
        printf("Interlace method    : %d\n",png_hdr.interlace);
        printf("Total size          : %llu bytes\n",png_hdr.totalSize);
        //printf("IDAT chunk size     : %u",png_hdr.idatSize);
    }
    else
    {
        printf("No\n");
        printf("Stats won't be shown since this is not a correct format.\n");
    }
}

size_t Get_Total_Image_Size(FILE *fileptr)
{
    // Move the cursor to the end (SEEK_END) to get the size and set cursor back to begining (SEEK_SET)
    fseek(fileptr,0,SEEK_END);
    size_t filesize = ftell(fileptr);
    fseek(fileptr,0,SEEK_SET);
    return filesize;
}

uint32_t Convert_bigEndian(uint8_t *data,int offset)
{
    // Reads the big endian value from the file, every byte and coverts. 
    return((uint32_t)data[offset] << 24 | (uint32_t)data[offset+1] << 16 | (uint32_t)data[offset+2] << 8 | (uint32_t)data[offset+3] );
}

png_header_t Get_PNG_Header(char* file_buffer, size_t filesize)
{
    png_header_t png_header;

    // PNG signature first 8 bytes (0-7)
    strncpy_s(png_header.png_sign,4,file_buffer+INDEX_START_PNG,3);

    // IHDR starts at byte 12 (12-15)
    strncpy_s(png_header.IHDR_verify,5,file_buffer+INDEX_START_IHDR,4);

    // Width starts at byte 16 (16-19)
    png_header.width = Convert_bigEndian((uint8_t*)file_buffer,INDEX_START_WIDTH);

    // Height starts at byte 20 (20-23)
    png_header.height = Convert_bigEndian((uint8_t*)file_buffer,INDEX_START_HEIGHT);

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

    // IDAT chunk data size
    png_header.idatSize = Convert_bigEndian((uint8_t*)file_buffer,INDEX_START_IDAT_SIZE);

    // Total size of the file
    png_header.totalSize = filesize;

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