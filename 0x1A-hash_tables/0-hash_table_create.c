#include <stdio.h>
#include <stdlib.h>

typedef struct hash_node {
    char* key;
    char* value;
    struct hash_node* next;
} hash_node_t;

typedef struct {
    unsigned long int size;
    hash_node_t** array;
} hash_table_t;

hash_table_t* hash_table_create(unsigned long int size) {
    hash_table_t* hash_table = (hash_table_t*)malloc(sizeof(hash_table_t));
    if (hash_table == NULL) {
        return NULL;
    }

    hash_table->size = size;
    hash_table->array = (hash_node_t**)calloc(size, sizeof(hash_node_t*));
    if (hash_table->array == NULL) {
        free(hash_table);
        return NULL;
    }

    return hash_table;
}

int main() {
    hash_table_t* hash_table = hash_table_create(10);
    if (hash_table == NULL) {
        printf("Failed to create hash table\n");
        return 1;
    }

    printf("Hash table created with size %lu\n", hash_table->size);

    return 0;
}

