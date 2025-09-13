#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "hashmap.h"

void test_insert_and_search() {
    hm_hashmap* hm = hm_new();
    hm_insert(hm, "name", "Jason");
    hm_insert(hm, "vegetable", "carrot");
    hm_insert(hm, "fruit", "strawberry");
    hm_insert(hm, "aquarium", "saltwater");

    assert(strcmp(hm_search(hm, "name"), "Jason") == 0);
    assert(strcmp(hm_search(hm, "vegetable"), "carrot") == 0);
    assert(strcmp(hm_search(hm, "fruit"), "strawberry") == 0);
    assert(strcmp(hm_search(hm, "aquarium"), "saltwater") == 0);

    hm_del_hashmap(hm);
    printf("test_insert_and_search passed\n");
}

void test_update_value() {
    hm_hashmap* hm = hm_new();
    hm_insert(hm, "fruit", "apple");
    hm_insert(hm, "fruit", "pear"); // overwrite

    assert(strcmp(hm_search(hm, "fruit"), "pear") == 0);

    hm_del_hashmap(hm);
    printf("test_update_value passed\n");
}

void test_delete_key() {
    hm_hashmap* hm = hm_new();
    hm_insert(hm, "vegetable", "spinach");
    hm_delete(hm, "vegetable");

    assert(hm_search(hm, "vegetable") == NULL);

    hm_del_hashmap(hm);
    printf("test_delete_key passed\n");
}

void test_collision_handling() {
    hm_hashmap* hm = hm_new();
    hm_insert(hm, "abc", "123");
    hm_insert(hm, "acb", "321"); // likely to collide depending on hash

    assert(strcmp(hm_search(hm, "abc"), "123") == 0);
    assert(strcmp(hm_search(hm, "acb"), "321") == 0);

    hm_del_hashmap(hm);
    printf("test_collision_handling passed\n");
}

int main() {
    test_insert_and_search();
    test_update_value();
    test_delete_key();
    test_collision_handling();
    return 0;
}
