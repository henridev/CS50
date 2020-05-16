#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover infile\n");
        return 1;
    }

    // remember filename
    char *infile = argv[1];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    unsigned char buffer[512];
    int filenumber = 0;
    char filename[8];

    FILE *outptr = NULL;

    // point to buffer to read into
    while (fread(&buffer, sizeof(buffer), 1, inptr))
    {
        // if butffer starts with what we expect
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // means if output is not null it means we found a new JPG begin
            // thus close the old one first
            if (outptr != NULL)
            {
                fclose(outptr);
            }

            // now open a file to which we will be able to write
            sprintf(filename, "%03i.jpg", filenumber++);
            printf("%s\n", filename);
            outptr = fopen(filename, "w");
            fwrite(&buffer, sizeof(buffer), 1, outptr);
        }

        // we already started writing
        else if (outptr != NULL)
        {
            fwrite(&buffer, sizeof(buffer), 1, outptr);
        }
    }

    free(buffer)
        fclose(inptr);
    fclose(outptr);
    return 0;
}
