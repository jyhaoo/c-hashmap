#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "hashmap.h"
#include "prime.h"

#define HM_PRIME_1 151
#define HM_PRIME_2 163

static hm_item HM_DELETED_ITEM = { NULL, NULL };

static hm_item* hm_new_item(const char* key, const char* value) {
    hm_item* item = malloc(sizeof(hm_item));
    item->key = strdup(key);
    item->value = strdup(value);
    return item;
}

hm_hashmap* hm_new() {
    return hm_new_sized(26);
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
    // Need to resize the hashmap when there are high rates of collision
    const int load = hashmap->count * 100 / hashmap->size;
    if (load > 70) {
        hm_resize_up(hashmap);
    }
    hm_item* item = hm_new_item(key, value);
    int index = hm_get_hash(key, hashmap->size, 0);
    hm_item* current_item = hashmap->items[index];
    int i = 1;
    while (current_item != NULL) {
        if (current_item != &HM_DELETED_ITEM) {
            if (strcmp(current_item->key, key) == 0) {
                hm_del_item(current_item);
                hashmap->items[index] = item;
                return;
            }
        }
        index = hm_get_hash(key, hashmap->size, i);
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
        if (item != &HM_DELETED_ITEM) {
            if (strcmp(item->key, key) == 0) {
                return item-> value;
            }
        }
        index = hm_get_hash(key, hashmap->size, i);
        item = hashmap->items[index];
        i++;
    }
    return NULL;
}

void hm_delete(hm_hashmap* hashmap, const char* key) {
    const int load = hashmap->count * 100 / hashmap->size;
    if (load < 10) {
        hm_resize_down(hashmap);
    }
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

static hm_hashmap* hm_new_sized(const int base_size) {
    hm_hashmap* hm = malloc(sizeof(hm_hashmap));
    hm->base_size = base_size;

    hm->size = next_prime(base_size);

    hm->count = 0;
    hm->items = calloc((size_t)hm->size, sizeof(hm_item*));
    return hm;
}

static void hm_resize(hm_hashmap* hm, const int base_size) {
    if (base_size < 26) {
        return;
    }

    hm_hashmap* new_hm = hm_new_sized(base_size);
    for (int i = 0; i < hm->size; i++) {
        hm_item* item = hm->items[i];
        if (item != NULL && item != &HM_DELETED_ITEM) {
            hm_insert(new_hm, item->key, item->value);
        }
    }

    const int tmp_size = hm->size;
    hm->size = new_hm->size;
    new_hm->size = tmp_size;

    hm_item** tmp_items = hm->items;
    hm->items = new_hm->items;
    new_hm->items = tmp_items;

    hm_del_hashmap(new_hm);
}

static void hm_resize_up(hm_hashmap* hm) {
    const int new_size = hm->base_size * 2;
    hm_resize(hm, new_size);
}

static void hm_resize_down(hm_hashmap* hm) {
    const int new_size = hm->base_size / 2;
    hm_resize(hm, new_size);
}