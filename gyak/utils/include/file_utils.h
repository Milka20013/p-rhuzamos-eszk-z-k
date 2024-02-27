#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include "string_utils.h"

/*
    Counts how many charachters are in the file, returns error if file can't be opened
*/
int count_chars_in_file(char *filename, int *number_of_chars);

/*
    Counts the number of lines in a file and the longest word length, returns error if file can't be opened
*/
int count_lengths_in_file(char *filename, int *lines, int *max_c_in_line);

/*
    Every char gets put in a string, returns error if file can't be opened
*/
int store_file_in_string(String *str, char *filename);

/*
    Every line gets put in a string array, the string array should be as big as the number of lines in file, returns error if file can't be opened
*/
int store_file_in_string_array(String *str, char *filename);

#endif