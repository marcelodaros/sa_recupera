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
    BYTE *buffer = malloc(12);

    fread(buffer, sizeof(BYTE), 12, raw_file);

    for(int i = 0; i < 12; i++)
    {
        printf("%x", buffer[i]);
    }
    printf("\n");
    return 0;
}