#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"strings.h"

string newEmptyString(int size) {
    string str = (string) malloc((size + 1) * sizeof(char));
    if(str == NULL) {
        printf("ERROR: Could not allocate memory for string\n");
        exit(EXIT_FAILURE);
    }

    return str;
}

string copyString(string str) {
    if(str == NULL) return NULL;

    string strf = newEmptyString(strlen(str));
    sprintf(strf, "%s", str);

    return strf;
}

string concat(string str1, string str2) {
    string str = newEmptyString(strlen(str1) + strlen(str2));
    sprintf(str, "%s%s", str1, str2);
    
    return str;
}

string slice(string str, int start, int end) {
    if(str == NULL) return NULL;

    int size = end - (start - 1) + 1;
    string sliced_str = newEmptyString(size);

    int j = 0;
    for(int i = start; i <= end; i++, j++) {
        sliced_str[j] = str[i];
    }
    sliced_str[j] = '\0';

    return sliced_str;
}

bool startsWith(string str1, string str2) {
    if(str1 == NULL || str2 == NULL) return false;

    int size1 = strlen(str1);
    int size2 = strlen(str2);

    if(size1 < size2) return false;

    for(int i = 0; i < size2; i++) {
        if(str1[i] != str2[i]) return false;
    }

    return true;
}

bool endsWith(string str1, string str2) {
    if(str1 == NULL || str2 == NULL) return false;

    int size1 = strlen(str1);
    int size2 = strlen(str2);

    if(size1 < size2) return false;

    for(int i = size1 - size2, j = 0; i < size1; i++, j++) {
        if(str1[i] != str2[j]) return false;
    }

    return true;
}

int contains(string str1, string str2) {
    if(str1 == NULL || str2 == NULL) return -1;

    int size1 = strlen(str1);
    int size2 = strlen(str2);

    if(size1 < size2) return -1;

    for(int i = 0, j = 0; i < size1; i++) {
        if(j != 0 && (str1[i] != str2[j])) j = 0;

        if(str1[i] == str2[j]) j++;

        if(j == size2) return i - j + 1;
    }

    return -1;
}

string join(int num_strings, string *strings, string joiner) {
    if(strings == NULL || joiner == NULL) return NULL;

    int size = 0;

    for(int i = 0; i < num_strings; i++)
        size += strlen(strings[i]) + strlen(joiner);
    
    string final_string = newEmptyString(size);
    final_string[0] = '\0';

    for(int i = 0; i < num_strings - 1; i++)
    {
        strcat(final_string, strings[i]);
        strcat(final_string, joiner);
    }
    strcat(final_string, strings[num_strings-1]);

    return final_string;
}