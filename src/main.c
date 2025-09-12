#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    hm_hashmap* map = hm_new();
    hm_del_hashmap(map);
    return 0;
}