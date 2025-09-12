#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "hashmap.h"

#define HM_PRIME_1 151
#define HM_PRIME_2 163

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

static void hm_del_item(hm_item* item) {
    free(item->key);
    free(item->value);
    free(item);
}

void hm_del_hashmap(hm_hashmap* hashmap) {
    for (int i = 0; i < hashmap->size; i++) {
        hm_item* item = hashmap-> items[i];
        if (item != NULL) {
            hm_del_item(item);
        }
    }
}

static int hm_hash(const char* key, const int a, const int m) {
    long hash = 0;
    const int key_len = (int)strlen(key);
    for (int i = 0; i < key_len; i++) {
        hash += (long)pow(a, key_len - (i + 1)) * key[i];
        hash = hash % m;
    }
    return (int)hash;
}

static int hm_get_hash(const char*key, const int num_buckets, const int attempt) {
    const int hash_a = hm_hash(key, HM_PRIME_1, num_buckets);
    const int hash_b = hm_hash(key, HM_PRIME_2, num_buckets);
    return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}

void hm_insert(hm_hashmap* hashmap, const char* key, const char* value) {
    hm_item* item = hm_new_item(key, value);
    int index = hm_get_hash(item->key, hashmap->size, 0);
    hm_item* current_item = hashmap->items[index];
    int i = 1;
    while (current_item != NULL) {
        index = hm_get_hash(item->key, hashmap->size, i);
        current_item = hashmap->items[index];
        i++;
    }
    hashmap->items[index] = item;
    hashmap->count++;
}

char* hm_search(hm_hashmap* hashmap, const char* key) {
    int index = hm_get_hash(key, hashmap->size, 0);
    hm_item* item = hashmap->items[index];
    int i = 1;
    while (item != NULL) {
        if (strcmp(item->key, key) == 0) {
            return item-> value;
        }
        index = hm_get_hash(key, hashmap->size, i);
        item = hashmap->items[index];
        i++;
    }
    return NULL;
}

static hm_item HM_DELETED_ITEM = { NULL, NULL };

void hm_delete(hm_hashmap* hashmap, const char* key) {
    int index = hm_get_hash(key, hashmap->size, 0);
    hm_item* item = hashmap->items[index];
    int i = 1;
    while (item != NULL) {
        if (item != &HM_DELETED_ITEM) {
            if (strcmp(item->key, key) ==0) {
                hm_del_item(item);
                hashmap->items[index] = &HM_DELETED_ITEM;
            }
        }
        index = hm_get_hash(key, hashmap->size, i);
        item = hashmap->items[index];
        i++;
    }
    hashmap->count--;
}