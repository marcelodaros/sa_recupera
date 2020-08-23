#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Define BYTE
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check usage of program
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover file.\n");
        return 1;
    }

    // Declare FILE pointers for out_jpegs and raw file
    FILE *out_jpeg = NULL;
    // If failed open raw file, prompt user and return 1
    FILE *raw_file = fopen(argv[1], "r");
    if (raw_file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 1;
    }

    // Alocate memory for buffer
    BYTE *buffer = malloc(512);

    // controlers for end of file and count of jpegs
    int eof = 0;
    int jpeg_count = 0;
    // Alocate memory for filenames of jpgs
    char *filename_jpeg = malloc(7);

    do
    {
        // Read the file. If eof < 512 Bytes, reached end of file.
        eof = fread(buffer, sizeof(BYTE), 512, raw_file);
        if (eof < sizeof(BYTE) * 512)
        {
            // write the last portion of data and break the loop
            fwrite(buffer, sizeof(BYTE), eof, out_jpeg);
            break;
        }

        // If found a header of jpeg file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] >= 0xe0 && buffer[3] <= 0xef)
        {
            // If it's the first image found, open first file and write buffer in it
            if (jpeg_count == 0)
            {
                sprintf(filename_jpeg, "%03i.jpg", jpeg_count);
                out_jpeg = fopen(filename_jpeg, "w");
                fwrite(buffer, sizeof(BYTE), 512, out_jpeg);
                jpeg_count++;
            }
            // If not first file, close current file and create a new one
            else
            {
                fclose(out_jpeg);
                sprintf(filename_jpeg, "%03i.jpg", jpeg_count);
                out_jpeg = fopen(filename_jpeg, "w");
                fwrite(buffer, sizeof(BYTE), 512, out_jpeg);
                jpeg_count++;
            }
        }
        // If writing a jpeg file, just do it
        else if (jpeg_count != 0)
        {
            fwrite(buffer, sizeof(BYTE), 512, out_jpeg);
        }

    }
    while (eof == sizeof(BYTE) * 512);

    // closing files and freeing mallocs
    free(buffer);
    free(filename_jpeg);
    fclose(raw_file);
    fclose(out_jpeg);
}