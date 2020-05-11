#include <cs50.h>
#include <stdio.h>

double liauIndex(int letters, int words, int sentences);

int main(void)
{
    string text = get_string("Text: ");
    int lettercount = 0;
    int wordcount = 1;
    int sentencecount = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        // when alphabet letter + 1 letter count
        if ((text[i] > 64 && text[i] < 91) || (text[i] > 96 && text[i] < 123))
        {
            lettercount++;
        }
        // when a space + 1 wordcount
        if (text[i] == 32)
        {
            wordcount++;
        }
        // when a ! ? or . + 1 sentences
        if (text[i] == 46 || text[i] == 63 || text[i] == 33)
        {
            sentencecount++;
        }
    }
    printf("%i letter(s)\n", lettercount);
    printf("%i words(s)\n", wordcount);
    printf("%i sentences(s)\n", sentencecount);

    double index = liauIndex(lettercount, wordcount, sentencecount);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", index);
    }
}

double liauIndex(int letters, int words, int sentences)
{
    double multiplier = (double)100 / (double)words;
    double L = (double)multiplier * (double)letters;
    double S = (double)multiplier * (double)sentences;
    double index = 0.0588 * L - 0.296 * S - 15.8;
    return index;
}