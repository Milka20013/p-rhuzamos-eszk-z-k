#include "include/file_utils.h"

#include <stdio.h>

int count_lengths_in_file(char *filename, int *lines, int *max_c_in_line)
{
    FILE *fp = fopen(filename, "r");
    if (fp == 0)
    {
        printf("Couldn't open the file");
        return 0;
    }
    char c = 'a';
    int i = 0;
    *max_c_in_line = 0;
    *lines = 1;
    while (c != EOF)
    {
        c = getc(fp);
        i++;
        if (c == '\n')
        {
            *lines = *lines + 1;
            if (*max_c_in_line < i - 1)
            {
                *max_c_in_line = i - 1;
            }
            i = 0;
        }
    }
    fclose(fp);
    return 1;
}

int count_chars_in_file(char *filename, int *number_of_chars)
{
    FILE *fp = fopen(filename, "r");
    if (fp == 0)
    {
        printf("Couldn't open the file");
        return 0;
    }

    int i = 0;
    while (getc(fp) != EOF)
    {
        i++;
    }
    *number_of_chars = i;

    fclose(fp);
    return 1;
}

int store_file_in_string(String *str, char *filename)
{
    FILE *fp = fopen(filename, "rb");
    if (fp == 0)
    {
        printf("Couldn't open the file");
        return 0;
    }
    int i = 0;
    char c = 'a';
    while (c != EOF)
    {
        c = getc(fp);
        str->content[i] = c;
        i++;
    }
    str->length = i;
    fclose(fp);
}

int store_file_in_string_array(String *str, char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == 0)
    {
        printf("Couldn't open the file");
        return 0;
    }
    char c = 'a';
    int i = 0;
    int lines = 0;
    while (c != EOF)
    {
        c = getc(fp);
        if (c != '\n')
        {
            str[lines].content[i] = c;
            i++;
        }
        else
        {
            constrain_string(&(str[lines]));
            lines++;
            i = 0;
        }
    }
    constrain_string(&(str[lines]));
    fclose(fp);
    return 1;
}