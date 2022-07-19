#include "EstructuraGrafo.h"
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>

dynamic_array_u32 new_dynamic_array(void)
{
    dynamic_array_u32 d_array = malloc(sizeof(dynamic_array_u32_St));
    d_array->capacity = 1;
    d_array->size = 0;
    d_array->array = malloc(1 * sizeof(u32));

    return d_array;
}

void dynamic_addr(dynamic_array_u32 d_array, u32 elem)
{
    u32 current_size = d_array->size;
    if (current_size < d_array->capacity)
    {
        d_array->array[current_size] = elem;
        d_array->size += 1;
    }
    else
    {
        u32 *old_array = d_array->array;
        u32 *new_array = malloc(current_size * 2 * sizeof(u32));
        for (u32 i = 0; i < current_size; i++)
            new_array[i] = old_array[i];
        new_array[current_size] = elem;

        d_array->capacity *= 2;
        d_array->size += 1;
        d_array->array = new_array;
        free(old_array);
    }

    return;
}

/* devuelve un ABB con vertice_name como único elemento */
static ABB_Vertices new_ABB(u32 vertice1_name, u32 vertice2_name)
{

    ABB_Vertices res_ABB = (ABB_Vertices)malloc(sizeof(ABB_Vertices_St));
    res_ABB->vecinos = new_dynamic_array();
    dynamic_addr(res_ABB->vecinos, vertice2_name);
    res_ABB->left_tree = NULL;
    res_ABB->right_tree = NULL;
    res_ABB->vertice_name = vertice1_name;

    return res_ABB;
}

/* Si vertice_name no está en _ABB:
    - agrega vertice_name a _ABB
    - devuelve U32_MAX y el puntero al nuevo nodo
   Si vertice_name sí está en _ABB:
    - devuelve el indice de verice_name en el array de vertices
      y el puntero NULL */
static void insert_vertice(ABB_Vertices abb, u32 vertice_name1, u32 vertice_name2)
{

    assert(abb != NULL);

    ABB_Vertices current_node;
    ABB_Vertices parent_node;

    current_node = abb;
    while (true)
    {
        parent_node = current_node;

        if (vertice_name1 != current_node->vertice_name)
        {

            if (vertice_name1 < current_node->vertice_name)
                current_node = current_node->left_tree;

            else if (vertice_name1 > current_node->vertice_name)
                current_node = current_node->right_tree;

            if (current_node == NULL)
            {

                if (vertice_name1 < parent_node->vertice_name)
                    parent_node->left_tree = new_ABB(vertice_name1, vertice_name2);
                else
                    parent_node->right_tree = new_ABB(vertice_name1, vertice_name2);

                break;
            }
        }

        else
        {
            dynamic_addr(current_node->vecinos, vertice_name2);
            break;
        }
    }

    return;
}

ABB_Vertices add_edge(u32 vertice_name1, u32 vertice_name2, ABB_Vertices abb)
{

    if (abb == NULL)
        abb = new_ABB(vertice_name1, vertice_name2);
    else
        insert_vertice(abb, vertice_name1, vertice_name2);

    insert_vertice(abb, vertice_name2, vertice_name1);

    return abb;
}