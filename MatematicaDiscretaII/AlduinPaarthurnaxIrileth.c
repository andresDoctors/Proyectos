#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "AlduinPaarthurnaxIrileth.h"

typedef struct Node_St
{
    u32 elem;
    struct Node_St *next;
} Node_St;

typedef struct List_St
{
    u32 size;
    struct Node_St *first;
    struct Node_St *last;
} List_St;

typedef List_St *List;

List enqueue(List list, u32 elem)
{
    Node_St *new_node = malloc(sizeof(Node_St));
    new_node->elem = elem;
    new_node->next = NULL;

    if (list == NULL)
    {
        list = malloc(sizeof(List_St));
        list->first = new_node;
        list->last = new_node;
        list->size  = 1;
        return list;
    }

    list->last->next = new_node;
    list->last = new_node;
    list->size++;

    return list;
}

u32 dequeue(List *list_ptr)
{
    if (*list_ptr == NULL)
        return 0xFFFFFFFF;

    u32 first_elem = (*list_ptr)->first->elem;
    Node_St *first_next = (*list_ptr)->first->next;

    free((*list_ptr)->first);
    (*list_ptr)->first = first_next;
    (*list_ptr)->size--;

    if (first_next == NULL)
    {
        free(*list_ptr);
        *list_ptr = NULL;
    }

    return first_elem;
}

u32 *Bipartito(Grafo G)
{

    u32 num_vertices = NumeroDeVertices(G);
    u32 *coloreo = calloc(num_vertices, sizeof(u32));
    bool *isVisited = calloc(num_vertices, sizeof(bool));
    u32 current_color;

    u32 *current_vecinos = calloc(Delta(G), sizeof(u32));
    u32 num_vecinos;
    u32 vecino;

    u32 current_vertice = 0;
    coloreo[0] = 1;
    isVisited[0] = true;
    List queue = NULL;

    bfs:
    while (queue != NULL || current_vertice != 0xFFFFFFFF)
    {

        num_vecinos = 0;
        vecino = IndiceONVecino(num_vecinos, current_vertice, G);
        while (vecino != 0xFFFFFFFF)
        {

            if (!isVisited[vecino])
            {
                queue = enqueue(queue, vecino);
                isVisited[vecino] = true;
            }

            current_vecinos[num_vecinos++] = vecino;
            vecino = IndiceONVecino(num_vecinos, current_vertice, G);
        }

        current_color = coloreo[current_vertice];
        for (u32 i = 0; i < num_vecinos; i++)
        {
            if (coloreo[current_vecinos[i]] == 0)
                coloreo[current_vecinos[i]] = (current_color % 2) + 1;

            else if (coloreo[current_vecinos[i]] == current_color)
            {
                free(coloreo);
                free(current_vecinos);
                free(isVisited);

                while (queue != NULL)
                    (void)dequeue(&queue);

                return NULL;
            }
        }

        current_vertice = dequeue(&queue);
    }

    // en caso de un grafo no conexo:
    for (u32 i = 0; i < num_vertices; i++)
        if (coloreo[i] == 0)
        {
            current_vertice = i;
            coloreo[i] = 1;
            isVisited[i] = true;
            goto bfs;
        }

    free(current_vecinos);
    free(isVisited);

    return coloreo;
}

u32 Greedy(Grafo G, u32 *Orden, u32 *Coloreo)
{
    u32 n = NumeroDeVertices(G);
    u32 _Delta = Delta(G);
    u32 grado;
    u32 vertice;
    u32 vecino;
    u32 num_cromatico = 0;

    // inicializacion
    Coloreo[Orden[0]] = 0;
    for (u32 i = 1u; i < n; i++)
        Coloreo[Orden[i]] = 0xFFFFFFFF;

    // greedy
    bool *is_used_color = malloc((_Delta + 1) * sizeof(bool));
    for (u32 i = 1u; i < n; i++)
    {
        vertice = Orden[i];
        grado = Grado(vertice, G);
        memset(is_used_color, false, (_Delta + 1) * sizeof(bool));
        for (u32 j = 0u; j < grado; j++)
        {
            vecino = IndiceONVecino(j, vertice, G);
            if (Coloreo[vecino] != 0xFFFFFFFF)
                is_used_color[Coloreo[vecino]] = true;
        }

        for (u32 j = 0u; j <= _Delta; j++)
        {
            if (!is_used_color[j])
            {
                Coloreo[vertice] = j;
                if (j > num_cromatico)
                    num_cromatico = j;

                break;
            }
        }
    }

    free(is_used_color);
    return num_cromatico + 1;
}

void AleatorizarKeys(u32 n, u32 R, u32 *key)
{
    srand(R);
    for (u32 i = 0; i < n; i++)
        key[i] = rand() % n;

    return;
}

int list_size_gt(const void *_a, const void *_b)
{
    List *a = (List *)_a;
    List *b = (List *)_b;

    u32 a_size = 0;
    if((*a) != NULL)
        a_size = (*a)->size;

    u32 b_size = 0;
    if((*b) != NULL)
        b_size = (*b)->size;

    return b_size - a_size;
}

u32 *RecoloreoCardinalidadDecrecienteBC(u32 n, u32 *Coloreo)
{

    List *indexes_of_color = calloc(n, sizeof(List));
    u32* Nuevo_coloreo = malloc(n * sizeof(u32));

    for (u32 i = 0; i < n; i++)
        indexes_of_color[Coloreo[i]] = enqueue(indexes_of_color[Coloreo[i]], i);

    qsort(indexes_of_color, n, sizeof(List), list_size_gt);

    List list_i;
    for (u32 i = 0; i < n; i++)
    {
        if (indexes_of_color[i] == NULL)
            break;

        list_i = indexes_of_color[i];

        while (list_i != NULL)
            Nuevo_coloreo[dequeue(&list_i)] = i;
    }

    free(indexes_of_color);
    return Nuevo_coloreo;
}

char OrdenFromKey(u32 n, u32* key, u32* Orden) {
    dynamic_array_u32* count = malloc(n * sizeof(dynamic_array_u32));
    if (count == NULL)
        return -1;

    u32 i;
    for(i = 0; i < n; i++)
        count[i] = new_dynamic_array();

    for (i = 0; i < n; i++)
        dynamic_addr(count[key[i]], i);

    u32 j = 0; 
    for(i = n - 1; i != 0xFFFFFFFF; i--)
        for (u32 k = 0; k < count[i]->size; k++)
            Orden[j++] = count[i]->array[k];

    for (i = 0; i < n; i++)
    {
        free(count[i]->array);
        free(count[i]);
    }

    free(count);

    return 0;
}

typedef struct tuple_u32_int {
    u32 old_color;
    int random;
} tuple_u32_int;

int tuple_u32_int_le(const void* _elem1_, const void* _elem2_) {
    tuple_u32_int* elem1 = (tuple_u32_int*) _elem1_;
    tuple_u32_int* elem2 = (tuple_u32_int*) _elem2_;

    return elem1->random - elem2->random;
}

u32 *PermutarColores(u32 n, u32 *Coloreo, u32 R) {

    u32 r = 0;
    for(u32 i = 0; i < n; i++)
        if(Coloreo[i] > r)
            r = Coloreo[i];

    srand(R);
    tuple_u32_int* map = malloc((r + 1) * sizeof(tuple_u32_int));
    for(u32 i = 0; i <= r; i++) {
        map[i].old_color = i;
        map[i].random = rand();
    }

    qsort(map, r + 1, sizeof(tuple_u32_int), tuple_u32_int_le);

    u32* new_coloreo = malloc(n * sizeof(u32));
    for (u32 i = 0; i < n; i++)
        new_coloreo[i] = map[Coloreo[i]].old_color;

    free(map);

    return new_coloreo;
}