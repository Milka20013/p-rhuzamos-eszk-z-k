#ifndef STRING_UTILS_H
#define STRING_UTILS_H

typedef struct
{
    char *content;
    int length;
} String;

/*
    Build a String from the char array
*/
void build_string(String *str, char *array);

/*
    Builds an empty String with a given length
*/
void build_empty_string(String *str, int length);

/*
    Recalculate the String's length according by the first '@' char
*/
void constrain_string(String *str);

/*
    Copies the content of the source String to the destination
*/
void copy_string(String *source, String *destination);

/*
    Check if the char is in the string, returns the index of the char or -1 if it wasn't found
*/
int contains(String *str, char c);

/*
    Reverses a string
*/
void reverse_string(String *str);

/*
    Makes a length size substring of the strs starting from index 0
*/
String *substring(String *str, int length);
#endif