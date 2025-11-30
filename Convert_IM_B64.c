#include "Convert_IM_B64.h"

void Print_Header_Stats(png_header_t png_hdr)
{
    printf("Width               : %u pixels\n",png_hdr.width);
    printf("Height              : %u pixels\n",png_hdr.height);
    printf("Bit depth           : %d\n",png_hdr.bitDepth);
    printf("Color Type          : %d\n",png_hdr.colorType );
    printf("Compression method  : %d\n",png_hdr.compression);
    printf("Filter method       : %d\n",png_hdr.filter);
    printf("Interlace method    : %d\n",png_hdr.interlace);
    printf("Total size          : %llu bytes\n",png_hdr.totalSize);
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

void ByteTo6Bit(char* file_buffer, size_t filesize, unsigned char* b64_buffer, size_t b64_filesize)
{
    (void) b64_filesize;

    size_t i;
    size_t j;
    // 8 bit to 6 bit using 24 bit, 24/8 = 3, 24/6 = 4.
    for(i = 0, j = 0; i < filesize; i+=3, j+=4)
    {
        // Check bounds before using, if out of bounds just use 0.
        unsigned char byte0 = file_buffer[i];
        unsigned char byte1 = (i + 1 < filesize) ? file_buffer[i+1] : 0;
        unsigned char byte2 = (i + 2 < filesize) ? file_buffer[i+2] : 0;

        // First 6 bits into b64_buffer[0].
        b64_buffer[j] = (byte0  >> 2) & 0x3F;
        // Last 2 bits of file_buffer[0] and first 4 bits of file_buffer[1] into b64_buffer[1].
        b64_buffer[j+1] = (((byte0  & 0x03) << 4) | (byte1 >> 4)) & 0x3F; 
        // Last 4 bits of file_buffer[1] and first 2 bits of file_buffer[2] into b64_buffer[2].
        b64_buffer[j+2] = (((byte1 & 0x0F) << 2) | ((byte2 & 0xC0) >> 6)) & 0x3F;
        // Last 6 bits of file_buffer[2] into b64_buffer[3].
        b64_buffer[j+3] = byte2 & 0x3F;
    }
}

void BitToB64(unsigned char* b64_buffer, size_t b64_filesize)
{
    // ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/
    size_t i;
    for(i = 0; i < b64_filesize; i++)
    {
        printf("%c",Base64_Table[b64_buffer[i]]);
    }
}

png_result_t Get_PNG_Header(char* file_buffer, size_t filesize)
{
    png_result_t png_result;

    // PNG signature first 8 bytes (0-7)
    strncpy_s(png_result.png_header.png_sign,4,file_buffer+INDEX_START_PNG,3);

    // Check if the image is a PNG.
    if(strcmp(png_result.png_header.png_sign,"PNG") == 0)
    {
        // IHDR starts at byte 12 (12-15)
        strncpy_s(png_result.png_header.IHDR_verify,5,file_buffer+INDEX_START_IHDR,4);

        // Width starts at byte 16 (16-19)
        png_result.png_header.width = Convert_bigEndian((uint8_t*)file_buffer,INDEX_START_WIDTH);

        // Height starts at byte 20 (20-23)
        png_result.png_header.height = Convert_bigEndian((uint8_t*)file_buffer,INDEX_START_HEIGHT);

        // Bit depth
        png_result.png_header.bitDepth = (uint8_t)file_buffer[INDEX_START_BITDEPTH];

        // Color type
        png_result.png_header.colorType = (uint8_t)file_buffer[INDEX_START_COLTYPE];

        // Compression method
        png_result.png_header.compression = (uint8_t)file_buffer[INDEX_START_COMPMET];

        // Filter method
        png_result.png_header.filter = (uint8_t)file_buffer[INDEX_START_FILTMET];

        // Interlance method
        png_result.png_header.interlace = (uint8_t)file_buffer[INDEX_START_INTERMET];

        // IDAT chunk data size
        png_result.png_header.idatSize = Convert_bigEndian((uint8_t*)file_buffer,INDEX_START_IDAT_SIZE);

        // Total size of the file
        png_result.png_header.totalSize = filesize;
        
        // Is a PNG.
        png_result.status = 0;
    }
    else
    {
        Set_Red_Text();
        printf("Image is not a PNG, please enter a correct format.\n");
        // Not a PNG.
        png_result.status = 1;
    }

    return png_result;
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