#ifndef __STR_SPLIT_H
#define __STR_SPLIT_H

#include "EstructuraGrafo.h"

#define NUM_OF_VISIBLE_CHARS 26 * 2 + 10 + 29

typedef struct Set_St
{
    char elem;
    struct Set_St *left;
    struct Set_St *right;
} Set_St;

typedef Set_St *Set;

typedef Set *HASH_OF_CHARS;

/* parsea el string 'str_source' en el array de strings 'str_target'
   retorna el numero de elementos */
u32 str_split(char *str_source, char *str_target[], char separator,
              HASH_OF_CHARS hash_table);

bool isVisible(char c, HASH_OF_CHARS hash_table);

HASH_OF_CHARS init_str_split(void);

bool is_in_set(Set set, char elem);

void destroy_hash_chars(HASH_OF_CHARS hash_table);

#endif