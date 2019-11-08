#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: recover data_file\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[1];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // define variables to be used in loop
    int bytes_read = 512; //End loop clause
    int file_index = 0; //For file naming
    char *image_address = malloc(7); //Store filename
    FILE *image; //File
    unsigned char buffer[512]; //Recovered data
    // Loop over 512bytes at the time, until less then 512 bytes is found.
    do
    {
        // Read 512 bytes, and store them in buffer, return how many bytes are read.
        bytes_read = fread(buffer, 1, 512, inptr);
        // If a jpg signature is found, create a new file, and write the data to that file.
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
        {
            sprintf(image_address, "%03i.jpg", file_index);
            file_index++;

            image = fopen(image_address, "w");
            fwrite(buffer, 1, 512, image);
        }
        // Store data to existing file if it is not the end of the file, and the first JPG signature has been found.
        else if (bytes_read == 512 && file_index != 0)
        {
            fwrite(buffer, 1, 512, image);
        }
    }
    while (bytes_read == 512);

    //Clear malloc
    free(image_address);
    // Return success
    return 0;
}



