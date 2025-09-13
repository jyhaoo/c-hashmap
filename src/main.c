#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    hm_hashmap* hm = hm_new();
    hm_insert(hm, "name", "Jason");
    hm_insert(hm, "vegetable", "carrot");
    hm_insert(hm, "fruit", "strawberry");
    hm_del_hashmap(hm);
    return 0;
}