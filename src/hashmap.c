#include <stdlib.h>
#include <string.h>

#include "hashmap.h"

static hm_item* hm_new_item(const char* key, const char* value) {
    hm_item* item = malloc(sizeof(hm_item));
    item->key = strdup(key);
    item->value = strdup(value);
    return item;
}

static hm_hashmap* hm_new(int size) {
    hm_hashmap* hashmap = malloc(sizeof(hm_hashmap));
    hashmap->size = size;
    hashmap->count = 0;
    hashmap->items = calloc((size_t)size, sizeof(hm_item*));
    return hashmap;
}