
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stdint.h"
#include "Convert_IM_B64.h"

int main()
{
    png_header_t png_header;
    char in_buffer[MAX_USER_INPUT];
    unsigned char in_file[MAX_BUFFER_SIZE];
    FILE *fileptr;

    // Ask file and open.
    fgets(in_buffer,MAX_USER_INPUT,stdin);
    in_buffer[strcspn(in_buffer,"\n")] = '\0';
    fileptr = fopen(in_buffer,"rb");

    // Read binary data into file buffer
    fread(in_file,1,MAX_BUFFER_SIZE,fileptr);

    // PNG signature first 8 bytes (0-7)
    strncpy_s(png_header.png_sign,4,(char*)in_file+1,3); // first char is garbage PNG start at byte 1 not 0

    // IHDR starts at byte 12 (12-15)
    strncpy_s(png_header.IHDR_verify,5,(char*)in_file+12,4);

    // Width starts at byte 16 (16-19)
    png_header.width = covert_bigEndian(in_file,16);

    // Height starts at byte 20 (20-23)
    png_header.height = covert_bigEndian(in_file,20);

    // Print
    Set_Blue_Text();
    printf(" %s\n %s\n Width %u\n Height : %u\n",
        png_header.png_sign,png_header.IHDR_verify,
        png_header.width,png_header.height);

    fclose(fileptr);
    Clean_();

    return 0;
}

