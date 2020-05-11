#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];

    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    for (int i = 0; key[i] != '\0'; i++)
    {
        if (!((key[i] >= 65 && key[i] <= 90) || (key[i] >= 97 && key[i] <= 122)))
        {
            printf("Invalid character in key\n");
            return 1;
        }
        for (int j = i + 1; j < strlen(key); j++)
        {
            if (key[i] == key[j])
            {
                printf("duplicate character in key\n");
                return 1;
            }
        }
    }

    string text = get_string("plaintext: ");
    string outputtext = text;

    int rankAlphabet;
    int encryptionLetter;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if ((text[i] >= 65 && text[i] <= 90))
        {
            rankAlphabet = text[i] - 65;
            encryptionLetter = key[rankAlphabet];
            if (encryptionLetter > 90)
            {
                encryptionLetter = key[rankAlphabet] - 32;
            }
            outputtext[i] = encryptionLetter;
        }
        else if ((text[i] >= 97 && text[i] <= 122))
        {
            rankAlphabet = text[i] - 97;
            encryptionLetter = key[rankAlphabet];
            if (encryptionLetter < 97)
            {
                encryptionLetter = key[rankAlphabet] + 32;
            }
            outputtext[i] = encryptionLetter;
        }
        else
        {
            outputtext[i] = text[i];
        }
    }

    printf("ciphertext: %s\n", outputtext);
}

