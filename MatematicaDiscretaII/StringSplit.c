#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "StringSplit.h"

Set add_to_set(Set set, char elem)
{

    if (set == NULL)
    {
        set = malloc(sizeof(Set_St));
        set->left = NULL;
        set->right = NULL;
        set->elem = elem;
        return set;
    }

    Set current_set = set;
    Set previous_set;
    while (current_set->elem != elem)
    {
        previous_set = current_set;

        if (elem < current_set->elem)
            current_set = current_set->left;

        else
            current_set = current_set->right;

        if (current_set == NULL)
        {
            current_set = malloc(sizeof(Set_St));
            current_set->left = NULL;
            current_set->right = NULL;
            current_set->elem = elem;

            if (elem < previous_set->elem)
                previous_set->left = current_set;
            else
                previous_set->right = current_set;
        }
    }

    return set;
}

HASH_OF_CHARS init_str_split(void)
{
    HASH_OF_CHARS hash_table = calloc(NUM_OF_VISIBLE_CHARS, sizeof(Set));
    char *visible_chars = calloc(NUM_OF_VISIBLE_CHARS + 1, sizeof(char));

    visible_chars = strcpy(visible_chars, "abcdefghijklmnopqrstuvwxyz");
    visible_chars = strcat(visible_chars, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    visible_chars = strcat(visible_chars, "0123456789");
    visible_chars = strcat(visible_chars, "!\"#%&'()*+,-./:;<=>?[\\]^_{|}~");

    u32 hash_code;
    for (u32 i = 0; i < NUM_OF_VISIBLE_CHARS; i++)
    {
        hash_code = visible_chars[i] % NUM_OF_VISIBLE_CHARS;
        hash_table[hash_code] = add_to_set(hash_table[hash_code], visible_chars[i]);
    }

    free(visible_chars);

    return hash_table;
}

bool is_in_set(Set set, char elem)
{
    while (true)
    {
        if (set == NULL)
            return false;

        if (elem < set->elem)
            set = set->left;
        else if (elem > set->elem)
            set = set->right;
        else
            return true;
    }
}

void destroy_set(Set set)
{
    if (set != NULL)
    {
        destroy_set(set->left);
        destroy_set(set->right);
        free(set);
    }

    return;
}

void destroy_hash_chars(HASH_OF_CHARS hash_table)
{
    for (u32 i = 0; i < NUM_OF_VISIBLE_CHARS; i++)
        destroy_set(hash_table[i]);
    free(hash_table);
    return;
}

bool isVisible(char c, HASH_OF_CHARS hash_table)
{
    u32 hash_code = c;
    hash_code = hash_code % NUM_OF_VISIBLE_CHARS;
    return is_in_set(hash_table[hash_code], c);
}

u32 str_split(char *str_source, char *str_target[], char separator,
              HASH_OF_CHARS hash_table)
{

    u32 word_number = -1;
    u32 word_index;
    u32 i = 0;

    while (str_source[i] != '\0')
    {
        while ((!isVisible(str_source[i], hash_table) || str_source[i] == separator) && str_source[i] != '\0')
            i += 1;

        if (str_source[i] == '\0')
            break;

        word_number += 1;
        word_index = 0;

        while (isVisible(str_source[i], hash_table) && str_source[i] != separator)
        {
            str_target[word_number][word_index] = str_source[i];
            word_index += 1;
            i += 1;
        }

        str_target[word_number][word_index] = '\0';
    }

    return (word_number + 1);
}