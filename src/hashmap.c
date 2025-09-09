#include <stdlib.h>
#include <string.h>

#include "hashmap.h"

static hm_item* hm_new_item(const char* key, const char* value) {
    hm_item* item = malloc(sizeof(hm_item));
    item->key = strdup(key);
    item->value = strdup(value);
    return item;
}

hm_hashmap* hm_new() {
    hm_hashmap* hashmap = malloc(sizeof(hm_hashmap));
    hashmap->size = 26;
    hashmap->count = 0;
    hashmap->items = calloc((size_t)hashmap->size, sizeof(hm_item*));
    return hashmap;
}

static void hm_free_item(hm_item* item) {
    free(item->key);
    free(item->value);
    free(item);
}

static void hm_free_hashmap(hm_hashmap* hashmap) {
    for (int i = 0; i < hashmap->size; i++) {
        hm_item* item = hashmap-> items[i];
        if (item != NULL) {
            hm_free_item(item);
        }
    }
}