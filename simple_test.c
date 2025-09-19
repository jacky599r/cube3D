#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

// Simple test without full cub3D dependencies
int main()
{
    printf("=== Testing Basic String Functions ===\n");
    
    // Test basic string operations
    char *test_str = "hello world";
    char *trimmed = malloc(12);
    strcpy(trimmed, "  hello  ");
    
    printf("Original: '%s'\n", trimmed);
    printf("Length: %zu\n", strlen(trimmed));
    
    // Test strndup equivalent
    char *dup = malloc(6);
    strncpy(dup, test_str, 5);
    dup[5] = '\0';
    printf("Duplicated first 5 chars: '%s'\n", dup);
    
    // Test numeric validation
    char *num_str = "12345";
    char *non_num = "12a34";
    int is_num = 1;
    
    for (int i = 0; num_str[i]; i++) {
        if (num_str[i] < '0' || num_str[i] > '9') {
            is_num = 0;
            break;
        }
    }
    printf("'%s' is numeric: %s\n", num_str, is_num ? "YES" : "NO");
    
    is_num = 1;
    for (int i = 0; non_num[i]; i++) {
        if (non_num[i] < '0' || non_num[i] > '9') {
            is_num = 0;
            break;
        }
    }
    printf("'%s' is numeric: %s\n", non_num, is_num ? "YES" : "NO");
    
    // Test empty line detection
    char *empty_line = "   \t\n";
    int is_empty = 1;
    for (int i = 0; empty_line[i]; i++) {
        if (empty_line[i] != ' ' && empty_line[i] != '\t' && 
            empty_line[i] != '\n' && empty_line[i] != '\r' &&
            empty_line[i] != '\v' && empty_line[i] != '\f') {
            is_empty = 0;
            break;
        }
    }
    printf("'%s' is empty line: %s\n", empty_line, is_empty ? "YES" : "NO");
    
    // Test map character validation
    char map_chars[] = {'0', '1', 'N', 'S', 'E', 'W', ' ', '\n', 'a', '2'};
    for (int i = 0; i < 10; i++) {
        int is_valid = (map_chars[i] == '0' || map_chars[i] == '1' ||
                       map_chars[i] == 'N' || map_chars[i] == 'S' ||
                       map_chars[i] == 'E' || map_chars[i] == 'W' ||
                       map_chars[i] == ' ' || map_chars[i] == '\n' ||
                       map_chars[i] == '\t' || map_chars[i] == '\r' ||
                       map_chars[i] == '\v' || map_chars[i] == '\f');
        printf("'%c' is valid map char: %s\n", map_chars[i], is_valid ? "YES" : "NO");
    }
    
    free(trimmed);
    free(dup);
    
    printf("\n=== All basic tests completed! ===\n");
    return (0);
}
