#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct hash_node {
    char* key;
    char* value;
    struct hash_node* next;
} hash_node_t;

typedef struct {
    unsigned long int size;
    hash_node_t** array;
} hash_table_t;

unsigned long int hash_djb2(const unsigned char* str) {
    unsigned long int hash = 5381;
    int c;

    while ((c = *str++) != 0) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

unsigned long int key_index(const unsigned char* key, unsigned long int size) {
    unsigned long int hash_value = hash_djb2(key);
    unsigned long int index = hash_value % size;
    return index;
}

int hash_table_set(hash_table_t* ht, const char* key, const char* value) {
    if (key == NULL || *key == '\0') {
        return 0;
    }

    unsigned long int index = key_index((const unsigned char*)key, ht->size);

    hash_node_t* node = ht->array[index];
    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            free(node->value);
            node->value = strdup(value);
            return 1;
        }
        node = node->next;
    }

    hash_node_t* new_node = (hash_node_t*)malloc(sizeof(hash_node_t));
    if (new_node == NULL) {
        return 0;
    }

    new_node->key = strdup(key);
    new_node->value = strdup(value);
    new_node->next = ht->array[index];
    ht->array[index] = new_node;

    return 1;
}

int main() {
    hash_table_t* hash_table = (hash_table_t*)malloc(sizeof(hash_table_t));
    hash_table->size = 10;
    hash_table->array = (hash_node_t**)calloc(hash_table->size, sizeof(hash_node_t*));

    hash_table_set(hash_table, "key1", "value1");
    hash_table_set(hash_table, "key2", "value2");
    hash_table_set(hash_table, "key3", "value3");

    hash_node_t* node = hash_table->array[key_index((const unsigned char*)"key1", hash_table->size)];
    while (node != NULL) {
        printf("%s: %s\n", node->key, node->value);
        node = node->next;
    }

    node = hash_table->array[key_index((const unsigned char*)"key2", hash_table->size)];
    while (node != NULL) {
        printf("%s: %s\n", node->key, node->value);
        node = node->next;
    }

    node = hash_table->array[key_index((const unsigned char*)"key3", hash_table->size)];
    while (node != NULL) {
        printf("%s: %s\n", node->key, node->value);
        node = node->next;
    }

    return 0;
}

