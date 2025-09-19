/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/XX XX:XX:XX by jacky599r         #+#    #+#             */
/*   Updated: 2025/01/XX XX:XX:XX by jacky599r        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

// Test function for ft_is_num
void test_ft_is_num()
{
    printf("Testing ft_is_num...\n");
    
    // Valid numeric strings
    assert(ft_is_num("123") == 1);
    assert(ft_is_num("0") == 1);
    assert(ft_is_num("999999") == 1);
    
    // Invalid strings
    assert(ft_is_num("12a3") == 0);
    assert(ft_is_num("abc") == 0);
    assert(ft_is_num("12.3") == 0);
    assert(ft_is_num("") == 0);
    assert(ft_is_num(NULL) == 0);
    assert(ft_is_num("12 3") == 0);
    
    printf("✓ ft_is_num tests passed\n");
}

// Test function for ft_is_empty_line
void test_ft_is_empty_line()
{
    printf("Testing ft_is_empty_line...\n");
    
    // Empty lines
    assert(ft_is_empty_line("") == 1);
    assert(ft_is_empty_line("   ") == 1);
    assert(ft_is_empty_line("\t\t") == 1);
    assert(ft_is_empty_line("\n\n") == 1);
    assert(ft_is_empty_line(" \t\n\r\v\f") == 1);
    
    // Non-empty lines
    assert(ft_is_empty_line("hello") == 0);
    assert(ft_is_empty_line("  hello  ") == 0);
    assert(ft_is_empty_line("\thello\n") == 0);
    
    printf("✓ ft_is_empty_line tests passed\n");
}

// Test function for ft_is_valid_map_char
void test_ft_is_valid_map_char()
{
    printf("Testing ft_is_valid_map_char...\n");
    
    // Valid map characters
    assert(ft_is_valid_map_char('0') == 1);
    assert(ft_is_valid_map_char('1') == 1);
    assert(ft_is_valid_map_char('N') == 1);
    assert(ft_is_valid_map_char('S') == 1);
    assert(ft_is_valid_map_char('E') == 1);
    assert(ft_is_valid_map_char('W') == 1);
    assert(ft_is_valid_map_char(' ') == 1);
    assert(ft_is_valid_map_char('\n') == 1);
    assert(ft_is_valid_map_char('\t') == 1);
    
    // Invalid map characters
    assert(ft_is_valid_map_char('a') == 0);
    assert(ft_is_valid_map_char('2') == 0);
    assert(ft_is_valid_map_char('@') == 0);
    assert(ft_is_valid_map_char('.') == 0);
    
    printf("✓ ft_is_valid_map_char tests passed\n");
}

// Test function for ft_whitetrim
void test_ft_whitetrim()
{
    printf("Testing ft_whitetrim...\n");
    
    char *result;
    
    // Test normal trimming
    result = ft_whitetrim("  hello  ");
    assert(strcmp(result, "hello") == 0);
    free(result);
    
    // Test with various whitespace
    result = ft_whitetrim("\t\nhello\r\v\f");
    assert(strcmp(result, "hello") == 0);
    free(result);
    
    // Test empty string
    result = ft_whitetrim("   ");
    assert(strcmp(result, "") == 0);
    free(result);
    
    // Test already trimmed
    result = ft_whitetrim("hello");
    assert(strcmp(result, "hello") == 0);
    free(result);
    
    printf("✓ ft_whitetrim tests passed\n");
}

// Test function for ft_strip_line_endings
void test_ft_strip_line_endings()
{
    printf("Testing ft_strip_line_endings...\n");
    
    char test1[] = "hello\n";
    char test2[] = "world\r\n";
    char test3[] = "test\r";
    char test4[] = "no_endings";
    char test5[] = "\n\n";
    
    ft_strip_line_endings(test1);
    assert(strcmp(test1, "hello") == 0);
    
    ft_strip_line_endings(test2);
    assert(strcmp(test2, "world") == 0);
    
    ft_strip_line_endings(test3);
    assert(strcmp(test3, "test") == 0);
    
    ft_strip_line_endings(test4);
    assert(strcmp(test4, "no_endings") == 0);
    
    ft_strip_line_endings(test5);
    assert(strcmp(test5, "") == 0);
    
    // Test NULL
    assert(ft_strip_line_endings(NULL) == NULL);
    
    printf("✓ ft_strip_line_endings tests passed\n");
}

// Test function for ft_strndup
void test_ft_strndup()
{
    printf("Testing ft_strndup...\n");
    
    char *result;
    
    // Test normal duplication
    result = ft_strndup("hello", 5);
    assert(strcmp(result, "hello") == 0);
    free(result);
    
    // Test with n smaller than string length
    result = ft_strndup("hello", 3);
    assert(strcmp(result, "hel") == 0);
    free(result);
    
    // Test with n larger than string length
    result = ft_strndup("hi", 10);
    assert(strcmp(result, "hi") == 0);
    free(result);
    
    // Test with n = 0
    result = ft_strndup("hello", 0);
    assert(strcmp(result, "") == 0);
    free(result);
    
    // Test NULL input
    assert(ft_strndup(NULL, 5) == NULL);
    
    printf("✓ ft_strndup tests passed\n");
}

// Test function for ft_img_init
void test_ft_img_init()
{
    printf("Testing ft_img_init...\n");
    
    t_img img;
    
    // Initialize with garbage values
    img.img = (void*)0x12345678;
    img.addr = (void*)0x87654321;
    img.bpp = 999;
    img.line = 888;
    img.endian = 777;
    
    ft_img_init(&img);
    
    assert(img.img == NULL);
    assert(img.addr == NULL);
    assert(img.bpp == 0);
    assert(img.line == 0);
    assert(img.endian == 0);
    
    // Test NULL input (should not crash)
    ft_img_init(NULL);
    
    printf("✓ ft_img_init tests passed\n");
}

// Test RGB functions
void test_rgb_functions()
{
    printf("Testing RGB functions...\n");
    
    // Test ft_is_rgb_within_range
    assert(ft_is_rgb_within_range(0, 0, 0) == PASS);
    assert(ft_is_rgb_within_range(255, 255, 255) == PASS);
    assert(ft_is_rgb_within_range(128, 64, 192) == PASS);
    
    assert(ft_is_rgb_within_range(-1, 0, 0) == FAIL);
    assert(ft_is_rgb_within_range(0, 256, 0) == FAIL);
    assert(ft_is_rgb_within_range(0, 0, -5) == FAIL);
    
    // Test ft_convert_rgb_to_int
    assert(ft_convert_rgb_to_int(0, 0, 0) == 0x000000);
    assert(ft_convert_rgb_to_int(255, 0, 0) == 0xFF0000);
    assert(ft_convert_rgb_to_int(0, 255, 0) == 0x00FF00);
    assert(ft_convert_rgb_to_int(0, 0, 255) == 0x0000FF);
    assert(ft_convert_rgb_to_int(255, 255, 255) == 0xFFFFFF);
    
    printf("✓ RGB functions tests passed\n");
}

// Test parameter validation functions
void test_param_validation()
{
    printf("Testing parameter validation...\n");
    
    // Test ft_is_valid_param
    assert(ft_is_valid_param("NO texture.xpm") == 1);
    assert(ft_is_valid_param("SO texture.xpm") == 1);
    assert(ft_is_valid_param("WE texture.xpm") == 1);
    assert(ft_is_valid_param("EA texture.xpm") == 1);
    assert(ft_is_valid_param("F 255,0,0") == 1);
    assert(ft_is_valid_param("C 0,255,0") == 1);
    
    assert(ft_is_valid_param("invalid line") == 0);
    assert(ft_is_valid_param("") == 0);
    assert(ft_is_valid_param("NO") == 0);
    
    printf("✓ Parameter validation tests passed\n");
}

int main()
{
    printf("=== Running cub3D Utility Functions Test Suite ===\n\n");
    
    test_ft_is_num();
    test_ft_is_empty_line();
    test_ft_is_valid_map_char();
    test_ft_whitetrim();
    test_ft_strip_line_endings();
    test_ft_strndup();
    test_ft_img_init();
    test_rgb_functions();
    test_param_validation();
    
    printf("\n=== All tests passed! ===\n");
    return (0);
}
