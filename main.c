
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stdint.h"
#include "Convert_IM_B64.h"

int main()
{
    png_header_t png_header;
    char in_buffer[MAX_USER_INPUT];
    FILE *fileptr;

    // Ask file.
    fgets(in_buffer,MAX_USER_INPUT,stdin);
    in_buffer[strcspn(in_buffer,"\n")] = '\0';

    // Open file 
    fileptr = fopen(in_buffer,"rb");

    // Allocate memory for buffer and get total size.
    size_t filesize = Get_Total_Image_Size(fileptr);
    char* file_buffer = malloc(filesize);

    // Allocate new memory buffer for 6bit b64 values.
    size_t b64_filesize = ((filesize * 8) / 6);
    unsigned char* b64_buffer = malloc(b64_filesize);

    // Read binary data into file buffer
    fread(file_buffer,1,filesize,fileptr);

    // Fill the header struct
    png_header = Get_PNG_Header(file_buffer,filesize);

    // Print
    Set_Blue_Text();
    Print_Header_Stats(png_header);
    
    // Convert to a 6 bit for b64
    ByteTo6Bit(file_buffer,filesize,b64_buffer,b64_filesize);
    
#ifdef DEBUG_Y
    printf("filebuffer[0] : %x --- b64buffer[0] : %x\n",(unsigned char)file_buffer[0], b64_buffer[0]);
    printf("filebuffer[1] : %x --- b64buffer[1] : %x\n",(unsigned char)file_buffer[1], b64_buffer[1]);
    printf("filebuffer[2] : %x --- b64buffer[2] : %x\n",(unsigned char)file_buffer[2], b64_buffer[2]);
    printf("filebuffer[3] : %x --- b64buffer[3] : %x\n",(unsigned char)file_buffer[3], b64_buffer[3]);
    printf("b64 file size : %llu\n",b64_filesize);
#endif

    // Convert to characters
    Set_Red_Text();
    printf("Base 64 : \n");
    BitToB64(b64_buffer,b64_filesize);

    // Close file and clean text
    fclose(fileptr);
    Clean_();

    return 0;
}

