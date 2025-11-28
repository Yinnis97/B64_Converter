
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

    // Read binary data into file buffer
    fread(file_buffer,1,filesize,fileptr);

    // Fill the header struct
    png_header = Get_PNG_Header(file_buffer,filesize);

    // Print
    Set_Blue_Text();
    Print_Header_Stats(png_header);
    
    // Close file and clean text
    fclose(fileptr);
    Clean_();

    return 0;
}

