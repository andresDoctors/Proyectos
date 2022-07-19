#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "StringSplit.h"
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"

#define MAX_NUM_OF_WORDS_PER_LINE 128
#define MAX_NUM_OF_CHARS_PER_WORD 128
#define MAX_NUM_OF_CHARS_PER_LINE 1024

#define IS_NATURAL(str) all(str, MAX_NUM_OF_CHARS_PER_WORD, '\0', isDigit)

bool debug = true;
#define DEBUG(x) \
    if (debug)   \
        printf(x);

#define DEBUGG(x, y) \
    if (debug)       \
        printf(x, y);

static bool isDigit(char x)
{
    return ('0' <= x && x <= '9');
}

static bool all(char *array, u32 len, char EOL, bool (*bool_func)(char))
{
    for (u32 i = 0; i < len && array[i] != EOL; i++)
        if (!bool_func(array[i]))
            return false;
    return true;
}

typedef struct ABB_name_index_St
{
    struct ABB_name_index_St *left;
    struct ABB_name_index_St *right;
    u32 name;
    u32 index;
} ABB_name_index_St;

typedef ABB_name_index_St *ABB_name_index;

typedef ABB_name_index *Hash_name_index;

typedef struct Stack_St
{
    struct Stack_St *next;
    ABB_Vertices elem;
} Stack_St;

typedef Stack_St *Stack;

Stack stack_push(ABB_Vertices elem, Stack stack)
{
    if (stack == NULL)
    {
        stack = malloc(sizeof(Stack_St));
        stack->elem = elem;
        stack->next = NULL;
    }
    else
    {
        Stack new = malloc(sizeof(Stack_St));
        new->elem = elem;
        new->next = stack;
        stack = new;
    }
    return stack;
}

ABB_Vertices stack_head(Stack stack)
{
    return stack->elem;
}

Stack stack_pop(Stack stack)
{
    assert(stack != NULL);

    Stack next = stack->next;
    free(stack);

    return next;
}

ABB_name_index new_hash_abb(u32 vertice_name, u32 vertice_index)
{
    ABB_name_index new = malloc(sizeof(ABB_name_index_St));
    new->left = NULL;
    new->right = NULL;
    new->index = vertice_index;
    new->name = vertice_name;

    return new;
}

typedef struct Stack_St2
{
    struct Stack_St2 *next;
    ABB_name_index elem;
} Stack_St2;

typedef Stack_St2 *Stack2;

Stack2 stack_push2(ABB_name_index elem, Stack2 stack)
{
    if (stack == NULL)
    {
        stack = malloc(sizeof(Stack_St));
        stack->elem = elem;
        stack->next = NULL;
    }
    else
    {
        Stack2 new = malloc(sizeof(Stack_St));
        new->elem = elem;
        new->next = stack;
        stack = new;
    }
    return stack;
}

ABB_name_index stack_head2(Stack2 stack)
{
    return stack->elem;
}

Stack2 stack_pop2(Stack2 stack)
{
    assert(stack != NULL);

    Stack2 next = stack->next;
    free(stack);

    return next;
}

void abb_hash_destroy(ABB_name_index abb)
{

    if (abb == NULL)
        return;

    Stack2 stack = NULL;
    ABB_name_index current_node = abb;
    ABB_name_index parent_node;

    while (current_node != NULL || stack != NULL)
    {

        while (current_node != NULL)
        {
            stack = stack_push2(current_node, stack);
            current_node = current_node->left;
        }

        if (stack != NULL)
        {
            parent_node = stack_head2(stack);
            stack = stack_pop2(stack);

            /* visit */
            current_node = parent_node->right;
            free(parent_node);
        }
    }

    return;
}

void add_to_hash_abb(ABB_name_index abb, u32 vertice_name, u32 vertice_index)
{

    assert(abb != NULL);

    ABB_name_index current_node;
    ABB_name_index parent_node;

    current_node = abb;
    while (true)
    {
        parent_node = current_node;

        if (vertice_name != current_node->name)
        {

            if (vertice_name < current_node->name)
                current_node = current_node->left;

            else if (vertice_name > current_node->name)
                current_node = current_node->right;

            if (current_node == NULL)
            {

                if (vertice_name < parent_node->name)
                    parent_node->left = new_hash_abb(vertice_name, vertice_index);
                else
                    parent_node->right = new_hash_abb(vertice_name, vertice_index);

                break;
            }
        }

        else
        {
            break;
        }
    }

    return;
}

void add_to_hash(u32 vertice_name, u32 vertice_index, Hash_name_index hash_table,
                 u32 num_vertices)
{

    u32 hash_code = vertice_name % num_vertices;

    if (hash_table[hash_code] == NULL)
        hash_table[hash_code] = new_hash_abb(vertice_name, vertice_index);
    else
        add_to_hash_abb(hash_table[hash_code], vertice_name, vertice_index);

    return;
}

void dfs(ABB_Vertices abb, dynamic_array_u32 *ord_vecinos_names,
         Hash_name_index hash_table, u32 num_vertices)
{

    assert(abb != NULL);

    u32 last_index = 0;
    Stack stack = NULL;
    ABB_Vertices current_node = abb;
    ABB_Vertices parent_node;

    while (current_node != NULL || stack != NULL)
    {

        while (current_node != NULL)
        {
            stack = stack_push(current_node, stack);
            current_node = current_node->left_tree;
        }

        if (stack != NULL)
        {
            parent_node = stack_head(stack);
            stack = stack_pop(stack);

            /* visit */
            ord_vecinos_names[last_index] = parent_node->vecinos;
            dynamic_addr(ord_vecinos_names[last_index], parent_node->vertice_name);

            add_to_hash(parent_node->vertice_name, last_index++, hash_table, num_vertices);
            current_node = parent_node->right_tree;
            free(parent_node);
        }
    }

    return;
}

u32 hash_find(Hash_name_index hash_table, u32 name, u32 num_vertices)
{
    ABB_name_index abb = hash_table[name % num_vertices];

    assert(abb != NULL);

    ABB_name_index current_node = abb;
    while (true)
    {
        assert(current_node != NULL);

        if (name != current_node->name)
        {

            if (name < current_node->name)
                current_node = current_node->left;

            else
                current_node = current_node->right;
        }

        else
        {
            break;
        }
    }

    return current_node->index;
}

u32 *translate(dynamic_array_u32 d_array, Hash_name_index hash_table, u32 len, u32 num_vertices)
{
    u32 *res = malloc(len * sizeof(u32));
    u32 name;
    u32 translation;
    for (u32 i = 0; i < len; i++)
    {
        name = d_array->array[i];
        translation = hash_find(hash_table, name, num_vertices);
        res[i] = translation;
    }
    return res;
}

void hash_destroy(Hash_name_index hash_table, u32 num_vertices)
{
    for (u32 i = 0; i < num_vertices; i++)
        abb_hash_destroy(hash_table[i]);
    free(hash_table);
    return;
}

Grafo abb_to_graph(ABB_Vertices abb, u32 num_vertices, u32 num_lados)
{

    dynamic_array_u32 *ord_vecinos_names = malloc(num_vertices * sizeof(dynamic_array_u32));

    Hash_name_index hash_table = calloc(num_vertices, sizeof(ABB_name_index));

    dfs(abb, ord_vecinos_names, hash_table, num_vertices);

    u32 size;
    Vertice *array_vertices = malloc(num_vertices * sizeof(Vertice));
    for (u32 i = 0; i < num_vertices; i++)
    {
        array_vertices[i] = malloc(sizeof(VerticeSt));

        size = ord_vecinos_names[i]->size;
        array_vertices[i]->grado = size - 1;
        array_vertices[i]->nombre = ord_vecinos_names[i]->array[size - 1];
        array_vertices[i]->vecinos = translate(ord_vecinos_names[i], hash_table, size - 1, num_vertices);

        free(ord_vecinos_names[i]->array);
        free(ord_vecinos_names[i]);
    }

    free(ord_vecinos_names);
    hash_destroy(hash_table, num_vertices);

    DEBUG("calculating Delta...\n")

    u32 _Delta = 0;
    u32 _Delta_index = 0;
    for (u32 i = 0; i < num_vertices; i++)
        if (_Delta < array_vertices[i]->grado)
        {
            _Delta = array_vertices[i]->grado;
            _Delta_index = i;
        }

    DEBUGG("Delta: %u\n", _Delta)
    DEBUGG("Delta_index: %u\n", _Delta_index)
    DEBUGG("vertice:%u\n", array_vertices[_Delta_index]->nombre)
    DEBUG("creating graph...\n")

    Grafo G = malloc(sizeof(GrafoSt));
    G->vertices = array_vertices;
    G->num_lados = num_lados;
    G->num_vertices = num_vertices;
    G->_Delta = _Delta;

    return G;
}

Grafo ConstruccionDelGrafo()
{

    DEBUG("allocating memory...\n")

    char *str_line = (char *)malloc(MAX_NUM_OF_CHARS_PER_LINE * sizeof(char));

    // char strWords[MAX_NUM_OF_WORDS_PER_LINE][MAX_NUM_OF_CHARS_PER_WORD];
    char **array_words = (char **)malloc(MAX_NUM_OF_WORDS_PER_LINE * sizeof(char *));
    for (u32 i = 0; i < MAX_NUM_OF_WORDS_PER_LINE; i++)
        array_words[i] = (char *)malloc(MAX_NUM_OF_CHARS_PER_WORD * sizeof(char));

    HASH_OF_CHARS hash_chars = init_str_split();

    DEBUG("ignoring lines...\n")

    // ignora las lineas con primera palabra "c"
    str_line = fgets(str_line, MAX_NUM_OF_CHARS_PER_LINE, stdin);

    printf("fst_line:%s", str_line);
    fflush(stdout);

    assert(str_line != NULL);
    u32 num_of_words = str_split(str_line, array_words, ' ', hash_chars);
    char *first_word = array_words[0];
    while (!strcmp(first_word, "c"))
    {
        str_line = fgets(str_line, MAX_NUM_OF_CHARS_PER_LINE, stdin);
        assert(str_line != NULL);
        num_of_words = str_split(str_line, array_words, ' ', hash_chars);
        first_word = array_words[0];
    }

    DEBUGG("current line: \"%s\"", str_line)
    DEBUG("getting graph metadata...\n")

    /* Verifica que la linea sea de la forma: "p edge n m"
       donde n y m son numeros narurales */
    assert(num_of_words == 4);
    assert(!strcmp(array_words[0], "p"));
    assert(!strcmp(array_words[1], "edge"));
    assert(IS_NATURAL(array_words[2]));
    assert(IS_NATURAL(array_words[3]));

    u32 num_of_vertices = atoi(array_words[2]);
    u32 num_of_edges = atoi(array_words[3]);

    DEBUGG("num_of_vertices: %u\n", num_of_vertices)
    DEBUGG("num_of_edges: %u\n", num_of_edges)

    DEBUG("adding edges...\n")

    ABB_Vertices abb = NULL;
    for (u32 i = 0; i < num_of_edges; i++)
    {

        str_line = fgets(str_line, MAX_NUM_OF_CHARS_PER_LINE, stdin);
        assert(str_line != NULL);
        num_of_words = str_split(str_line, array_words, ' ', hash_chars);

        assert(num_of_words == 3);
        assert(!strcmp(array_words[0], "e"));
        assert(IS_NATURAL(array_words[1]));
        assert(IS_NATURAL(array_words[2]));

        abb = add_edge(atoi(array_words[1]), atoi(array_words[2]), abb);
    }

    DEBUG("freeing up memory(hashChars)...\n")

    destroy_hash_chars(hash_chars);

    DEBUG("freeing up memory(strings)...\n")
    free(str_line);

    for (u32 i = 0; i < MAX_NUM_OF_WORDS_PER_LINE; i++)
        free(array_words[i]);
    free(array_words);

    Grafo g = abb_to_graph(abb, num_of_vertices, num_of_edges);

    return g;
}

void DestruccionDelGrafo(Grafo G)
{
    u32 num_of_vertices = G->num_vertices;
    for (u32 i = 0; i < num_of_vertices; i++)
    {
        free(G->vertices[i]->vecinos);
        free(G->vertices[i]);
    }
    free(G->vertices);
    free(G);
}

u32 NumeroDeVertices(Grafo G)
{
    return G->num_vertices;
}

u32 NumeroDeLados(Grafo G)
{
    return G->num_lados;
}

u32 Delta(Grafo G)
{
    return G->_Delta;
}

u32 Nombre(u32 i, Grafo G)
{
    if (i < G->num_vertices)
        return G->vertices[i]->nombre;
    return U32_MAX;
}

u32 Grado(u32 i, Grafo G)
{
    if (i < G->num_vertices)
        return G->vertices[i]->grado;
    return U32_MAX;
}

u32 IndiceONVecino(u32 j, u32 k, Grafo G)
{
    if (k < G->num_vertices)
        if (j < G->vertices[k]->grado)
            return G->vertices[k]->vecinos[j];

    return U32_MAX;
}

/*static void printGrafo(Grafo G) {
    for (u32 v_index = 0; v_index < NumeroDeVertices(G); v_index++)
    {
        printf("index:%u\tname:%u\n", v_index, Nombre(v_index, G));
        for (u32 vecinos = 0; vecinos < Grado(v_index, G); vecinos++)
        {
            u32 vecino_index = IndiceONVecino(vecinos, v_index, G);
            printf("\tvecino_num:%u\tvecino_index:%u\tvecino_name:%u\n",
                   vecinos, vecino_index, Nombre(vecino_index, G));
        }
    }
}
*/