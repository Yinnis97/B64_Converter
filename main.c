
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

    png_header = Get_PNG_Header((char*)in_file);

    // Print
    Set_Blue_Text();
    Print_Header_Stats(png_header);
    
    fclose(fileptr);
    Clean_();

    return 0;
}

