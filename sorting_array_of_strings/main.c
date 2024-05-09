/***********************************************************************************************
Author : Karim Zidan
Linkedin: https://www.linkedin.com/in/karimzidanelsayed/

************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to compare two strings lexicographically
int lexicographic_sort(const char* a, const char* b) {
    unsigned char i = 0;
    unsigned char state;
    
    // Compare characters until the end of one of the strings is reached
    while ((a[i] != '\0') || (b[i] != '\0')) {
        if (a[i] > b[i]) {
            state = 1;
            break;
        } else if (a[i] == b[i]) {
            i++;
        } else {
            state = 0;
            break;
        }
    }
    return state;
}

// Function to compare two strings lexicographically in reverse
int lexicographic_sort_reverse(const char* a, const char* b) {
    unsigned char i = 0;
    unsigned char state;
    
    // Compare characters until the end of one of the strings is reached
    while ((a[i] != '\0') || (b[i] != '\0')) {
        if (a[i] < b[i]) {
            state = 1;
            break;
        } else if (a[i] == b[i]) {
            i++;
        } else {
            state = 0;
            break;
        }
    }
    return state;
}

// Function to sort strings by the number of distinct characters
int sort_by_number_of_distinct_characters(const char* a, const char* b) {
    unsigned int distinct_numbers_of_a = 0;
    unsigned int distinct_numbers_of_b = 0;
    unsigned int found = 0;

    // Count distinct characters in string a
    for (int i = 0; a[i + 1] != '\0'; i++) {
        for (int x = i + 1; a[x] != '\0'; x++) {
            if (a[i] == a[x]) {
                found = 0;
                break;
            } else {
                found = 1;
            }
        }
        if (1 == found) {
            distinct_numbers_of_a++;
            found = 0;
        }
    }
    
    found = 0;

    // Count distinct characters in string b
    for (int i = 0; b[i + 1] != '\0'; i++) {
        for (int x = i + 1; b[x] != '\0'; x++) {
            if (b[i] == b[x]) {
                found = 0;
                break;
            } else {
                found = 1;
            }
        }
        if (1 == found) {
            distinct_numbers_of_b++;
            found = 0;
        }
    }

    if (distinct_numbers_of_a > distinct_numbers_of_b) {
        return 1;
    } else if (distinct_numbers_of_a == distinct_numbers_of_b) {
        return lexicographic_sort(a, b);
    } else {
        return 0;
    }
}

// Function to sort strings by length
int sort_by_length(const char* a, const char* b) {
    unsigned int length_of_a = 0;
    unsigned int length_of_b = 0;
    unsigned int x = 0;
    
    // Calculate the length of string a
    while (a[x] != '\0') {
        length_of_a++;
        x++;
    }
    x = 0;
    
    // Calculate the length of string b
    while (b[x] != '\0') {
        length_of_b++;
        x++;
    }
    x = 0;
    
    if (length_of_a > length_of_b) {
        return 1;
    } else if (length_of_a == length_of_b) {
        return lexicographic_sort(a, b);
    } else {
        return 0;
    }
}

// Function to sort an array of strings using a comparison function
void string_sort(char** arr, const int len, int (*cmp_func)(const char* a, const char* b)) {
    char* temp_string = NULL;
    unsigned int state = 0;
    
    for (int i = 0; i < len - 1; i++) {
        for (int x = i + 1; x < len; x++) {
            state = cmp_func(arr[i], arr[x]);
            if (1 == state) {
                temp_string = arr[i];
                arr[i] = arr[x];
                arr[x] = temp_string;
            }
        }
    }
}
