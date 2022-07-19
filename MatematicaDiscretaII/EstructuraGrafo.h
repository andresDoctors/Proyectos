#ifndef __ESTRUCTURA_GRAHO_H
#define __ESTRUCTURA_GRAHO_H

#include <limits.h>

typedef unsigned int u32;
#define U32_MAX UINT_MAX

typedef struct dynamic_array_u32_St
{
    u32 size;
    u32 capacity;
    u32 *array;
} dynamic_array_u32_St;

typedef dynamic_array_u32_St *dynamic_array_u32;

typedef struct VerticeSt
{
    u32 nombre;
    u32 grado;
    u32 color;
    u32 *vecinos;
} VerticeSt;

typedef VerticeSt *Vertice;

typedef struct ABB_Vertices_St
{
    u32 vertice_name;
    u32 vertice_index;
    dynamic_array_u32 vecinos;
    struct ABB_Vertices_St *left_tree;
    struct ABB_Vertices_St *right_tree;
} ABB_Vertices_St;

typedef ABB_Vertices_St *ABB_Vertices;

typedef struct GrafoSt
{
    u32 num_vertices;
    u32 num_lados;
    u32 _Delta;
    Vertice *vertices;
} GrafoSt;

/* O(1)
   Si vertice_name no se encuentra en abb_vertices:
    - Añade el nuevo vertice a abb_vertices
    - Le asigna una posicion en el array vertices
    - Añade el puntero del nuevo nodo a free_array para luego poder destruir
        el abb_vertices facilmente
   Si vertice_name se encuentra en abb_vertices:
    - Encuentra su nodo en abb_vertices y obtiene su indice en el array vertices
    - Le agrega el nuevo vecino */
ABB_Vertices add_edge(u32 verrice_name1, u32 vertice_name2, ABB_Vertices abb);

void dynamic_addr(dynamic_array_u32 d_array, u32 elem);

dynamic_array_u32 new_dynamic_array(void);

#endif