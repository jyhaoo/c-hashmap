typedef struct {
    char* key;
    char* value;
} hm_item;

typedef struct {
    int size;
    int count;
    hm_item** items;
} hm_hashmap;